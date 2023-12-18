#include "page_06.h"
#include "ui_page_06.h"

Page_06::Page_06(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Page_06)
{
    ui->setupUi(this);
    this->setWindowTitle("设置页面");
    /*返回主页面*/
    connect(ui->exitButton,&QPushButton::clicked,[=](){emit back();});
    /*跳转至串口设置页面*/
    portSets = PortSettings::get_ins();
    connect(ui->portSet_Button,&QPushButton::clicked,[=](){portSets->show();});
    connect(portSets,&PortSettings::back,[=](){portSets->hide();});
    /*跳转至相机设置页面：page06_01 */
    page06_01 = new Page06_1;
    connect(ui->camSets_Button,&QPushButton::clicked,[=](){this->hide();page06_01->show();});
    connect(page06_01,&Page06_1::back,[=](){page06_01->hide();this->show();});
    /*跳转至恒流源板调节页面：page06_02 */
    page06_02 = new Page06_2;
    connect(ui->lightAdjButton,&QPushButton::clicked,[=](){this->hide();page06_02->show();});
    connect(page06_02,&Page06_2::back,[=](){page06_02->hide();this->show();});
    /*跳转至图像获取页面：page06_03 */
    page06_03 = new Page06_3;
    connect(ui->imageGetButton,&QPushButton::clicked,[=](){this->hide();page06_03->show();});
    connect(page06_03,&Page06_3::back,[=](){page06_03->hide();this->show();});
}

Page_06::~Page_06()
{
    delete ui;
}
