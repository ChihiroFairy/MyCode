#include "writeprocess.h"

/*
 * 单例模式 *
*/
writeProcess * writeProcess::writePro = nullptr;
writeProcess *writeProcess::get_ins()
{

    if(writePro == nullptr) {
        writePro = new writeProcess();
    }
    return writePro;
}

writeProcess::writeProcess(QObject *parent) : QObject(parent)
{

}
writeProcess::~writeProcess()
{
    delete writePro;
}
/*
 * 函数：sendCommand()
 * 参数：functionCode，data1，data2
 * 功能：将传入的三个参数作为指令数据使用write()函数发送
 * 备注：在实例化该发送类的地方调用
 */
void writeProcess::sendCommand(const QString &functionCode, const QString &data1, const QString &data2) {
    QByteArray frame = createFrame(functionCode, data1, data2);
    serialPort.write(frame);
    qDebug()<<"message:"<<frame.toUpper().toHex();
}

/*
 * 函数：calculateChecksum()
 * 参数：data
 * 功能：逐位异或校验，返回校验结果
 * 备注：
 */
quint8 writeProcess::calculateChecksum(const QByteArray &data) {
    quint8 checksum = 0;
    for (int i = 0; i < data.size(); ++i) {
        checksum ^= static_cast<quint8>(data.at(i));
    }
    return checksum;
}

/*
 * 函数：createFrame()
 * 参数：functionCode，data1，data2
 * 功能：将传入的指令内容根据通信协议组成一帧完整指令，并返回指令帧frame
 * 备注：
 */
QByteArray writeProcess::createFrame(const QString &functionCode, const QString &data1, const QString &data2) {
    QByteArray frame;
    frame.append(0x5A);  // 帧头
    frame.append(functionCode.toUInt(nullptr, 16));
    frame.append(data1.toUInt(nullptr, 16));
    frame.append(data2.toUInt(nullptr, 16));
    frame.append(calculateChecksum(frame.left(4)));  // 前4个字节异或校验
    frame.append(0xFF);  // 帧尾

    return frame;
}
