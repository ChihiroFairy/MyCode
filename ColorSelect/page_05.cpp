#include "page_05.h"
#include "ui_page_05.h"

Page_05::Page_05(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Page_05)
{
    ui->setupUi(this);
    this->setWindowTitle("模型页面");
    /*返回主页面*/
    connect(ui->exitButton,&QPushButton::clicked,[=](){emit back();});
    //******************写处理对象调用***********************
    writePro = writeProcess::get_ins();
    //******************界面显示***********************
}

Page_05::~Page_05()
{
    delete ui;
}

/*
 * 函数：on_changeButton_clicked()
 * 参数：
 * 功能：切换模型
 * 备注：
 */
void Page_05::on_changeButton_clicked()
{
    //暂定为第一种算法
    writePro->sendCommand("40","00","01");
}
