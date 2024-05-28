#include "pageopen.h"
#include "ui_pageopen.h"
#include <QDesktopWidget>

PageOpen::PageOpen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PageOpen)
{
    ui->setupUi(this);
    //窗口显示在屏幕正中间
    QDesktopWidget *homePage = QApplication::desktop();
    move((homePage->width()-this->width())/2,(homePage->height()-this->height())/2);

    //下料指令标志初始化为false
    started = false;
    //******************写处理对象调用***********************
    writePro = writeProcess::get_ins();

    //******************信号槽连接********************************
    /*返回至主页面*/
    connect(ui->exitButton,&QPushButton::clicked,[=](){emit back();});

    //******************图标样式设置********************************
    ui->startStopButton->setStyleSheet(
     "QPushButton{"
     "border-image: url(:/new/icon/icon/start.png);"
     "border-radius: 20px;"
     "border:5px 11c4d4;"
     "background-color:#ADB4B9;"
     "border-style:inset;"
     "color:rgba(0,0,0,100);"
     "}");
}

PageOpen::~PageOpen()
{
    delete ui;
}

/*
 * 函数：on_startStopButton_clicked()
 * 参数：
 * 功能：点击startStopButton按钮发送开始下料指令
 * 备注：发送开始下料指令
 */
void PageOpen::on_startStopButton_clicked()
{
    if(!started){
        writePro->sendCommand("01","00","11");
        ui->startStopButton->setStyleSheet(
            "QPushButton{"
            "border-image: url(:/new/icon/icon/running.png);"
            "border-radius: 20px;"
            "border:5px 11c4d4;"
            "background-color:#ADB4B9;"
            "font:bold 10px;"
            "color:rgba(0,0,0,100);"
        "}");
        ui->startOpen_Label->setText("停止下料");
        qDebug()<<"开始下料！";
        started = true;
    }
    else{
        writePro->sendCommand("01","00","00");
        ui->startStopButton->setStyleSheet(
         "QPushButton{"
         "border-image: url(:/new/icon/icon/start.png);"
         "border-radius: 20px;"
         "border:5px 11c4d4;"
         "background-color:#ADB4B9;"
         "border-style:inset;"
         "color:rgba(0,0,0,100);"
         "}");
        ui->startOpen_Label->setText("开始下料");
        qDebug()<<"停止下料！";
        started = false;
    }
}
