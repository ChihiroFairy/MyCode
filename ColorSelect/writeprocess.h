#ifndef WRITEPROCESS_H
#define WRITEPROCESS_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include <QMutex>
#include <QtSerialPort/QSerialPort>         // 提供访问串口的功能
#include <QtSerialPort/QSerialPortInfo>     // 提供系统中存在的串口信息
#include "portcom.h"
#include "logrecorder.h"

class writeProcess : public QObject
{
    Q_OBJECT
public:
    explicit writeProcess(QObject *parent = nullptr);
    ~writeProcess();

    //使用单例模式
    static writeProcess *get_ins();
    static writeProcess *writePro;

    void sendCommand(const QString &functionCode, const QString &data1, const QString &data2);

public slots:
    //void sendCommand(const QString &functionCode, const QString &data1, const QString &data2);

private:
    quint8 calculateChecksum(const QByteArray &data);
    QByteArray createFrame(const QString &functionCode, const QString &data1, const QString &data2);

};

#endif // WRITEPROCESS_H
