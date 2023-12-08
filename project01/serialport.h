#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QObject>
#include <QtSerialPort/QSerialPort>         // 提供访问串口的功能
#include <QtSerialPort/QSerialPortInfo>     // 提供系统中存在的串口信息
#include <QDebug>
#include "portsettings.h"
#include "ui_portsettings.h"
#include "preproccess.h"

//定义全局变量
extern QSerialPort serialPort;

//防止循环引用
class preproccess;
class SerialPort : public QObject
{
    Q_OBJECT
public:
    explicit SerialPort(QObject *parent = nullptr);
    ~SerialPort();

signals:

public slots:
    void close_Port();//关闭串口
//    void read_Data();//数据接收
    void init_Port();
private:
    //串口参数配置对象
    portSettings *portSetting;
    preproccess *prePross;
};

#endif // SERIALPORT_H
