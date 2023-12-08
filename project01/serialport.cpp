#include "serialport.h"

//全局串口对象
QSerialPort serialPort;

SerialPort::SerialPort(QObject *parent) : QObject(parent)
{
    portSetting = portSettings::get_ins();
    prePross = preproccess::get_ins();

    init_Port();
    connect(portSetting->ui->saveButton,&QPushButton::clicked,this,&SerialPort::init_Port);
}
SerialPort::~SerialPort()
{
    close_Port();
}

void SerialPort::init_Port()
{
    qDebug()<<"已执行！";
    //串口参数配置
    //    设置串口号
    serialPort.setPortName(portSetting->ui->combo_portName->currentText());
    //    设置波特率
    switch (portSetting->ui->combo_baudRate->currentIndex()) {
    case 0:
        serialPort.setBaudRate(QSerialPort::Baud1200);
        break;
    case 1:
        serialPort.setBaudRate(QSerialPort::Baud2400);
        break;
    case 2:
        serialPort.setBaudRate(QSerialPort::Baud4800);
        break;
    case 3:
        serialPort.setBaudRate(QSerialPort::Baud9600);
        break;
    case 4:
        serialPort.setBaudRate(QSerialPort::Baud19200);
        break;
    case 5:
        serialPort.setBaudRate(QSerialPort::Baud38400);
        break;
    case 6:
        serialPort.setBaudRate(QSerialPort::Baud57600);
        break;
    case 7:
        serialPort.setBaudRate(QSerialPort::Baud115200);
        break;
    default:
        serialPort.setBaudRate(QSerialPort::Baud9600);
        break;
    }
    //    设置数据位
    switch (portSetting->ui->combo_dataBits->currentIndex()) {
    case 0:
        serialPort.setDataBits(QSerialPort::Data5);
        break;
    case 1:
        serialPort.setDataBits(QSerialPort::Data6);
        break;
    case 2:
        serialPort.setDataBits(QSerialPort::Data7);
        break;
    case 3:
        serialPort.setDataBits(QSerialPort::Data8);
        break;
    default:
        serialPort.setDataBits(QSerialPort::Data8);
        break;
    }
    //  设置停止位
    switch (portSetting->ui->combo_stopBits->currentIndex()) {
    case 0:
        serialPort.setStopBits(QSerialPort::OneStop);
        break;
    case 1:
        serialPort.setStopBits(QSerialPort::OneAndHalfStop);
        break;
    case 2:
        serialPort.setStopBits(QSerialPort::TwoStop);
        break;
    default:
        serialPort.setStopBits(QSerialPort::OneStop);
        break;
    }
    //  设置检查位
    switch (portSetting->ui->combo_parityBits->currentIndex()) {
    case 0:
        serialPort.setParity(QSerialPort::NoParity);
        break;
    case 1:
        serialPort.setParity(QSerialPort::EvenParity);
        break;
    case 2:
        serialPort.setParity(QSerialPort::OddParity);
        break;
    default:
        serialPort.setParity(QSerialPort::NoParity);
        break;
    }

    //设置内部读缓冲区的大小（如果不设置默认最大是4096字节）
    //serialPort.setReadBufferSize(1);

    //测试
    qDebug() << serialPort.portName();
    qDebug() << serialPort.baudRate()<<portSetting->ui->combo_baudRate->currentText();
    qDebug() << serialPort.stopBits()<<portSetting->ui->combo_stopBits->currentText();
    qDebug() << serialPort.dataBits()<<portSetting->ui->combo_dataBits->currentText();
    qDebug() << serialPort.parity()<<portSetting->ui->combo_parityBits->currentText();

    //串口打开
    if(serialPort.isOpen())
    {
        //不做操作
    }
    else
    {
        if(serialPort.open(QIODevice::ReadWrite))
        {
          qDebug()<<"串口打开成功！";
        }
        else
        {
          qDebug()<<"串口打开失败！"<< serialPort.errorString();
        }
    }
}
void SerialPort::close_Port()
{
    if(serialPort.isOpen())
    {
        serialPort.clear();//清空串口缓冲区的数据
        qDebug()<<"正在清空串口缓冲区！";
        serialPort.close();//关闭串口
        qDebug()<<"串口已关闭！";
        serialPort.deleteLater();//随后删除该串口对象，与new对应
        qDebug()<<"串口已删除！";
    }
}
