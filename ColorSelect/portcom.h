#ifndef PORTCOM_H
#define PORTCOM_H

#include <QObject>
#include <QtSerialPort/QSerialPort>         // 提供访问串口的功能
#include <QtSerialPort/QSerialPortInfo>     // 提供系统中存在的串口信息
#include <QDebug>
#include "portsettings.h"
#include "ui_portsettings.h"

//定义全局变量
extern QSerialPort serialPort;

class PortCom : public QObject
{
    Q_OBJECT
public:
    explicit PortCom(QObject *parent = nullptr);
    ~PortCom();

signals:

public slots:
    //打开串口
    void init_Port();
    //关闭串口
    void close_Port();
private:
    //串口参数配置对象
    PortSettings *portSetting;
};

#endif // PORTCOM_H
