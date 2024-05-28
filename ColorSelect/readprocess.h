#ifndef READPROCESS_H
#define READPROCESS_H

#include <QObject>
#include <QtSerialPort/QSerialPort>         // 提供访问串口的功能
#include <QtSerialPort/QSerialPortInfo>     // 提供系统中存在的串口信息
#include <QThread>
#include <QMutex>
#include "portcom.h"

class readProcess : public QObject
{
    Q_OBJECT
public:
    explicit readProcess(QObject *parent = nullptr);
    ~readProcess();

    //使用单例模式
    static readProcess *get_ins();
    static readProcess *readPro;

signals:
    /*串口接收到的数据分发信号*/
    void data_Page_01(const QByteArray &data);
    void data_Page_02(const QByteArray &data);
    void data_Page_05(const QByteArray &data);

public slots:
    void read_Data();//数据接收

private:
    //接收数据缓存
    QByteArray receiveBuffer;

    QThread *readThread;
    QMutex mutex;
    void parseFrame(const QByteArray &data);
    bool verifyChecksum(const QByteArray &payload);
    void processFrame(const QByteArray &frameData);

};

#endif // READPROCESS_H
