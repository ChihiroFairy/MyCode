#ifndef PREPROCCESS_H
#define PREPROCCESS_H

#include <QObject>
#include <QtSerialPort/QSerialPort>         // 提供访问串口的功能
#include <QtSerialPort/QSerialPortInfo>     // 提供系统中存在的串口信息
#include "serialport.h"
#include <QThread>
#include "device02.h"
#include "mainwindow.h"

//防止循环引用
class SerialPort;
class device02;
class MainWindow;
class preproccess : public QObject
{
    Q_OBJECT
public:
    explicit preproccess(QObject *parent = nullptr);
    ~preproccess();

    //使用单例模式
    static preproccess *get_ins();
    static preproccess *prePross;

signals:
    void dataReceivedDevice02(const QByteArray &data);
    void dataReceivedMainWindow(const QByteArray &data);

public slots:
    void read_Data();//数据接收

private:
    //接收数据缓存
    QByteArray receiveBuffer;

    void parseFrame(const QByteArray &data);
    bool verifyChecksum(const QByteArray &payload);
    void processFrame(const QByteArray &frameData);
};

#endif // PREPROCCESS_H
