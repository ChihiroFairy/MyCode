#include "preproccess.h"

preproccess::preproccess(QObject *parent) : QObject(parent)
{
    connect(&serialPort,SIGNAL(readyRead()),this,SLOT(read_Data()));
}
preproccess::~preproccess()
{

}
/*
 * 单例模式 *
*/
preproccess * preproccess::prePross= nullptr;
preproccess *preproccess::get_ins()
{
    if(prePross == nullptr) {
        prePross = new preproccess();
    }
    return prePross;
}

void preproccess::read_Data()
{
    receiveBuffer.append(serialPort.readAll());
    parseFrame(receiveBuffer);
}

// 数据解析
void preproccess::parseFrame(const QByteArray &data)
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
//异或校验
bool preproccess::verifyChecksum(const QByteArray &data)
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

//数据分发
void preproccess::processFrame(const QByteArray &payload)
{
    qDebug() << "payload:" << payload.toHex();

    //裁切出核心数据
    QByteArray receData = payload.mid(1, 3);

    // Assuming function code is at index 1
    char functionCode = receData.at(0);

    switch (functionCode)
    {
    case 0x01:
        emit dataReceivedDevice02(receData);
        break;

    case 0x02:
        emit dataReceivedMainWindow(receData);
        break;

    // Handle other function codes...

    default:
        qDebug() << "Unknown function code: " << QString::number(static_cast<quint8>(functionCode), 16).toUpper();
        break;
    }

    qDebug() << "分发函数已执行！";
}
