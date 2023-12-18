#include "portsettings.h"
#include "ui_portsettings.h"

/*
 * 单例模式 *
*/
PortSettings * PortSettings::portSet = nullptr;
PortSettings *PortSettings::get_ins()
{
    if(portSet == nullptr) {
        portSet = new PortSettings();
    }
    return portSet;
}

PortSettings::PortSettings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PortSettings)
{
    ui->setupUi(this);
    portsets();
    /*返回设置页面*/
    connect(ui->exitButton,&QPushButton::clicked,[=](){emit back();});

}

PortSettings::~PortSettings()
{
    delete ui;
    delete portSet;
}

void PortSettings::portsets()
{
    //串口配置显示
    //串口号
    foreach(const QSerialPortInfo &info,QSerialPortInfo::availablePorts())
    {
        ui->combo_portName->addItem(info.portName());
        //本机可用串口为ttyS1，索引号为1
        ui->combo_portName->setCurrentIndex(1);
        qDebug()<<"可用串口:"<<info.portName();
    }
    //波特率配置
    ui->combo_baudRate->addItem("1200");
    ui->combo_baudRate->addItem("2400");
    ui->combo_baudRate->addItem("4800");
    ui->combo_baudRate->addItem("9600");
    ui->combo_baudRate->addItem("19200");
    ui->combo_baudRate->addItem("38400");
    ui->combo_baudRate->addItem("57600");
    ui->combo_baudRate->addItem("115200");
    ui->combo_baudRate->setCurrentIndex(3);
    //数据位配置
    ui->combo_dataBits->addItem("5");
    ui->combo_dataBits->addItem("6");
    ui->combo_dataBits->addItem("7");
    ui->combo_dataBits->addItem("8");
    ui->combo_dataBits->setCurrentIndex(3);
    //校验位
    ui->combo_parityBits->addItem("No");
    ui->combo_parityBits->addItem("even");
    ui->combo_parityBits->addItem("odd");
    ui->combo_parityBits->setCurrentIndex(0);
    //停止位
    ui->combo_stopBits->addItem("OneStop");
    ui->combo_stopBits->addItem("OneAndHalfStop");
    ui->combo_stopBits->addItem("TwoStop");
    ui->combo_stopBits->setCurrentIndex(0);

}

