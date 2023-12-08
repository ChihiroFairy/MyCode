#include "device02.h"
#include "ui_device02.h"
#include <QTimer>
#include <QTime>

device02::device02(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::device02)
{
    ui->setupUi(this);
    connect(ui->exitButton,&QPushButton::clicked,[=](){
        emit back();
    });

    prePross = preproccess::get_ins();
    // 连接信号到槽函数
    connect(prePross, &preproccess::dataReceivedDevice02, this, &device02::upDateDisplay);
}
/*
 * 单例模式 *
*/
device02 * device02::dev02 = nullptr;
device02 *device02::get_ins()
{
    if(dev02 == nullptr) {
        dev02 = new device02();
    }
    return dev02;
}

device02::~device02()
{
    delete ui;
}
void device02::on_sendButton_clicked()
{
    QString data = "5A000101";
    QByteArray sendData = QByteArray::fromHex(data.toUtf8());
    serialPort.write(sendData);
    qDebug()<<"02窗口发送："<<data;
}
void device02::upDateDisplay(const QByteArray &data)
{
    qDebug() << "Device02 Updated Display: " << data;
    ui->receText->setText(data.toHex());
}
