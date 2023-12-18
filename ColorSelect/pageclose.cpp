#include "pageclose.h"
#include "ui_pageclose.h"

PageClose::PageClose(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PageClose)
{
    ui->setupUi(this);

    /*返回至主页面*/
    connect(ui->exitButton,&QPushButton::clicked,[=](){emit back();});
}

PageClose::~PageClose()
{
    delete ui;
}
