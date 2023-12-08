#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include "device02.h"
#include <QDateTime>
#include <QString>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    dev02 = new device02;
    connect(ui->switchButton,&QPushButton::clicked,[=](){
        this->hide();
        dev02->show();
    });
    connect(dev02,&device02::back,[=](){
        dev02->hide();
        this->show();
    });

    portSetting = portSettings::get_ins();
    connect(ui->portSetting,&QPushButton::clicked,[=](){
        portSetting->show();
    });
    connect(portSetting,&portSettings::back,[=](){
        portSetting->hide();
    });

    prePross = preproccess::get_ins();
    // 连接信号到槽函数
    connect(prePross, &preproccess::dataReceivedMainWindow, this, &MainWindow::upDateDisplay);

    qDebug()<<"主线程："<<thread()->currentThreadId();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_sendButton_clicked()
{
    QString data = "5A000101";
    QByteArray sendData = QByteArray::fromHex(data.toUtf8());
    serialPort.write(sendData);
    qDebug()<<"主窗口发送："<<data;
}

void MainWindow::upDateDisplay(const QByteArray &data)
{
    qDebug() << "MainWindow Updated Display: " << data;
    ui->receData->setText(data.toHex());
}
