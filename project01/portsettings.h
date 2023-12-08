#ifndef PORTSETTINGS_H
#define PORTSETTINGS_H

#include <QWidget>
#include <QtSerialPort/QSerialPort>         // 提供访问串口的功能
#include <QtSerialPort/QSerialPortInfo>     // 提供系统中存在的串口信息

namespace Ui {
class portSettings;
}

class portSettings : public QWidget
{
    Q_OBJECT

public:
    explicit portSettings(QWidget *parent = nullptr);
    ~portSettings();
    void portsets();

    //使用单例模式
    static portSettings *get_ins();
    static portSettings *portSet;

public slots:

signals:
    void back();

//此处将私有域更改为公有域
public:
    Ui::portSettings *ui;

    QString port;
    int baudRate;
    int data;
    int stop;
    int check;
};

#endif // PORTSETTINGS_H
