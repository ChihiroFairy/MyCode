#include "readprocess.h"

/*
 * 单例模式 *
*/
readProcess * readProcess::readPro= nullptr;
readProcess *readProcess::get_ins()
{
    if(readPro == nullptr){
        readPro = new readProcess();
    }
    return readPro;
}

readProcess::readProcess(QObject *parent) : QObject(parent)
{
    readThread = new QThread();
    this->moveToThread(readThread);
    connect(&serialPort,SIGNAL(readyRead()),this,SLOT(read_Data()));
    readThread->start();
}
readProcess::~readProcess()
{
    delete readPro;
    readThread->quit();
    readThread->wait();
}

/*
 * 函数：read_Data()
 * 参数：receiveBuffer
 * 功能：使用串口读取函数将读取到的数据存放至receiveBuffer缓冲中，用于下一步解析
 * 备注：
 */
void readProcess::read_Data()
{
    qDebug()<<"readThread:"<<QThread().currentThreadId();

    receiveBuffer.append(serialPort.readAll());
    parseFrame(receiveBuffer);
}

/*
 * 函数：parseFrame()
 * 参数：data
 * 功能：对接收到的数据按通信协议规定进行逐帧解析
 * 备注：
 */
void readProcess::parseFrame(const QByteArray &data)
{
    const char frameStart = 0x5A; // 帧头
    const char frameEnd = 0xFF;   // 帧尾

    int frameStartIndex = data.indexOf(frameStart);
    int frameEndIndex = data.indexOf(frameEnd);

    while (frameStartIndex != -1 && frameEndIndex != -1 && frameEndIndex > frameStartIndex)
    {
        QByteArray frameData = data.mid(frameStartIndex, frameEndIndex - frameStartIndex + 1);
        if (verifyChecksum(frameData))
        {
            processFrame(frameData);
            receiveBuffer.remove(0, frameEndIndex + 1); // Remove processed data
        }
        else
        {
            qDebug() << "Checksum error!";
            receiveBuffer.remove(0, frameStartIndex + 1); // Remove invalid frame start
        }

        frameStartIndex = data.indexOf(frameStart);
        frameEndIndex = data.indexOf(frameEnd);
    }
}

/*
 * 函数：verifyChecksum()
 * 参数：data
 * 功能：对解析出的一帧数据进行异或校验，并返回校验bool值
 * 备注：
 */
bool readProcess::verifyChecksum(const QByteArray &data)
{
    // 校验数据长度是否符合要求
    if (data.size() != 6) {
        qDebug() << "Invalid data length";
        return false;
    }

    // 异或校验
    char xorResult = 0;
    for (int i = 0; i < 4; ++i) {
        xorResult ^= data.at(i);
    }

    // 将校验结果转换为十六进制字节
    QByteArray hexXORResult;
    hexXORResult.append(xorResult);

    // 将校验结果与第5个字节进行比较
    return (hexXORResult.toHex() == data.mid(4, 1).toHex());
}

/*
 * 函数：processFrame()
 * 参数：payload
 * 功能：对通过校验的指令帧按功能码进行对应窗口数据转发
 * 备注：使用信号槽形式转发对应界面的数据
 */
void readProcess::processFrame(const QByteArray &payload)
{
    //裁切出核心数据
    QByteArray receData = payload.mid(1, 3);

    // Assuming function code is at index 1
    char functionCode = receData.at(0);

    switch (functionCode)
    {
    case 0x01:
        emit data_Page_01(receData);
        break;

    case 0x02:
        emit data_Page_02(receData);
        break;

    // Handle other function codes...

    default:
        qDebug() << "Unknown function code: " << QString::number(static_cast<quint8>(functionCode), 16).toUpper();
        break;
    }
}
