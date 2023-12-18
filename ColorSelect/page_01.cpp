#include "page_01.h"
#include "ui_page_01.h"

Page_01::Page_01(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Page_01)
{
    ui->setupUi(this);
    this->setWindowTitle("精度页面");
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
