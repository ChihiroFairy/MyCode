#include "page06_3.h"
#include "ui_page06_3.h"
#include <QDesktopWidget>

Page06_3::Page06_3(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Page06_3)
{
    ui->setupUi(this);

    //窗口显示在屏幕正中间
    QDesktopWidget *homePage = QApplication::desktop();
    move((homePage->width()-this->width())/2,(homePage->height()-this->height())/2);

    /*返回主页面*/
    connect(ui->exitButton,&QPushButton::clicked,[=](){emit back();});
    //******************写处理对象调用***********************
    writePro = writeProcess::get_ins();
    //******************界面显示***********************

    //端口自动补全以及默认提示
    ui->portLineEdit->setPlaceholderText(tr("5000"));//设置默认提示
    QStringList portWordList;
    portWordList << tr("5000");
    QCompleter* portCompleter = new QCompleter(portWordList, this);
    ui->portLineEdit->setCompleter(portCompleter);

    connect(&tcpServer, SIGNAL(newConnection()),this, SLOT(acceptConnection()));

    ui->imageLabel_qz->show();
    ui->imageLabel_hz->show();
}

Page06_3::~Page06_3()
{
    delete ui;
}

void Page06_3::on_qianCam_Button_clicked()
{
    ui->imageWidget->setCurrentIndex(0);
}

void Page06_3::on_houCam_Button_clicked()
{
    ui->imageWidget->setCurrentIndex(1);
}

void Page06_3::on_getImage_Button_clicked()
{
    if(0 == ui->imageWidget->currentIndex())
    {
        //前主相机获取图像
        writePro->sendCommand("3c","0a","01");
    }
    else {
        //后主相机获取图像
        writePro->sendCommand("3d","0a","01");
    }
}
void Page06_3::start()
{
    if (!tcpServer.listen(QHostAddress::LocalHost, ui->portLineEdit->text().toInt())) {
        qDebug() << tcpServer.errorString();
        close();
        return;
    }

    totalBytes = 0;
    bytesReceived = 0;
    imageSize = 0;
    ui->serverStatusLabel->setText(tr("正在监听"));

}

void Page06_3::acceptConnection()
{
    //获得链接套接字
    tcpServerConnection = tcpServer.nextPendingConnection();

    //接收数据
    //readyRead()当网络套接字上有新的网络数据有效负载时
    connect(tcpServerConnection, SIGNAL(readyRead()),
            this, SLOT(updateServerProgress()));
    //处理异常
    connect(tcpServerConnection, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(displayError(QAbstractSocket::SocketError)));

    ui->serverStatusLabel->setText(tr("接受连接"));
    // 关闭服务器，不再进行监听
//    tcpServer.close();
}


void Page06_3::updateServerProgress()
{
    QDataStream in(tcpServerConnection);
    in.setVersion(QDataStream::Qt_5_12);

    // 如果接收到的数据小于16个字节，保存到来的文件头结构
    if (bytesReceived <= sizeof(qint64)*2) {
        if((tcpServerConnection->bytesAvailable() >= sizeof(qint64)*2)
                && (imageSize == 0)) {
            // 接收数据总大小信息和文件名大小信息
            in >> totalBytes  >> imageSize;
            bytesReceived += sizeof(qint64) * 2;

            if(imageSize == 0){
                  ui->serverStatusLabel->setText(tr("显示的图片为空!"));
            }
              qDebug() <<"定位点0" << endl;
        }
        if((tcpServerConnection->bytesAvailable() >= imageSize)
                && (imageSize != 0)) {

            // 接收文件名，并建立文件
            in >> imageContent;

//            qDebug() << imageContent << endl;

            ui->serverStatusLabel->setText(tr("接收文件 …"));

            QImage imageData = getImage(imageContent);

            QPixmap resImage = QPixmap::fromImage(imageData);
            QPixmap* imgPointer = &resImage;
            imgPointer->scaled(ui->imageLabel_qz->size(), Qt::IgnoreAspectRatio);//重新调整图像大小以适应窗口
           // imgPointer->scaled(ui->imageLabel->size(), Qt::KeepAspectRatio);//设置pixmap缩放的尺寸

            ui->imageLabel_qz->setScaledContents(true);//设置label的属性,能够缩放pixmap充满整个可用的空间。
            ui->imageLabel_qz->setPixmap(*imgPointer);

            bytesReceived += imageSize;

            qDebug() << "定位1  bytesReceived: " << bytesReceived << endl;

            if(bytesReceived == totalBytes){
                 ui->serverStatusLabel->setText(tr("接收文件成功"));
                 totalBytes = 0;
                 bytesReceived = 0;
                 imageSize = 0;
            }

         }
     }
}

void Page06_3::displayError(QAbstractSocket::SocketError socketError)
{
    qDebug() <<"errorString()" <<tcpServerConnection->errorString();
    tcpServerConnection->close();

    ui->serverStatusLabel->setText(tr("服务端就绪"));

}

QImage Page06_3::getImage(const QString &data)
{
    QByteArray imageData = QByteArray::fromBase64(data.toLatin1());
    QImage image;
    image.loadFromData(imageData);
    return image;
}

// 开始监听按钮

void Page06_3::on_startButton_clicked()
{
    if(ui->startButton->text() == tr("监听")){
        ui->startButton->setText(tr("断开"));
        start();
    }else{
        ui->startButton->setText(tr("监听"));
        tcpServer.close();

        tcpServerConnection->disconnectFromHost();
    }
}
