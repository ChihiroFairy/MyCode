#ifndef PORTSETTINGS_H
#define PORTSETTINGS_H

#include <QWidget>
#include <QtSerialPort/QSerialPort>         // 提供访问串口的功能
#include <QtSerialPort/QSerialPortInfo>     // 提供系统中存在的串口信息
#include <QDebug>

namespace Ui {
class PortSettings;
}

class PortSettings : public QWidget
{
    Q_OBJECT

public:
    explicit PortSettings(QWidget *parent = nullptr);
    ~PortSettings();
    void portsets();

    //使用单例模式
    static PortSettings *get_ins();
    static PortSettings *portSet;

public slots:

signals:
    //返回设置页面
    void back();

//此处将私有域更改为公有域
public:
    Ui::PortSettings *ui;

    QString port;
    int baudRate;
    int data;
    int stop;
    int check;

};

#endif // PORTSETTINGS_H
