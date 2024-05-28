#include "page_01.h"
#include "ui_page_01.h"
#include <QDesktopWidget>

Page_01::Page_01(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Page_01)
{
    ui->setupUi(this);
    this->setWindowTitle("精度页面");

    //窗口显示在屏幕正中间
    QDesktopWidget *homePage = QApplication::desktop();
    move((homePage->width()-this->width())/2,(homePage->height()-this->height())/2);

    /*返回主页面*/
    connect(ui->exitButton,&QPushButton::clicked,[=](){emit back();});
    //******************写处理对象调用***********************
    writePro = writeProcess::get_ins();
    //******************界面显示***********************
}

Page_01::~Page_01()
{
    delete ui;
}
