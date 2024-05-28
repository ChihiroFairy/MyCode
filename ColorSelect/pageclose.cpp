#include "pageclose.h"
#include "ui_pageclose.h"
#include <QDesktopWidget>

PageClose::PageClose(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PageClose)
{
    ui->setupUi(this);
    //窗口显示在屏幕正中间
    QDesktopWidget *homePage = QApplication::desktop();
    move((homePage->width()-this->width())/2,(homePage->height()-this->height())/2);

    /*返回至主页面*/
    connect(ui->exitButton,&QPushButton::clicked,[=](){emit back();});
}

PageClose::~PageClose()
{
    delete ui;
}
