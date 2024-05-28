#include "page_06.h"
#include "ui_page_06.h"
#include <QDesktopWidget>
#include <QGraphicsDropShadowEffect>

Page_06::Page_06(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Page_06)
{
    ui->setupUi(this);
    this->setWindowTitle("设置页面");


    /*图标显示*/
    //部件阴影效果
    QGraphicsDropShadowEffect *shadoweffect_00 = new QGraphicsDropShadowEffect;
    //阴影色, 透明度
    shadoweffect_00->setColor(QColor(100,100,100));
    shadoweffect_00->setBlurRadius(10);//阴影模糊半径
    shadoweffect_00->setOffset(5);    //阴影偏移
    ui->camKindButton->setGraphicsEffect(shadoweffect_00);

    //部件阴影效果
    QGraphicsDropShadowEffect *shadoweffect_01 = new QGraphicsDropShadowEffect;
    //阴影色, 透明度
    shadoweffect_01->setColor(QColor(100,100,100));
    shadoweffect_01->setBlurRadius(10);//阴影模糊半径
    shadoweffect_01->setOffset(5);    //阴影偏移
    ui->camSigButton->setGraphicsEffect(shadoweffect_01);

    //部件阴影效果
    QGraphicsDropShadowEffect *shadoweffect_02 = new QGraphicsDropShadowEffect;
    //阴影色, 透明度
    shadoweffect_02->setColor(QColor(100,100,100));
    shadoweffect_02->setBlurRadius(10);//阴影模糊半径
    shadoweffect_02->setOffset(5);    //阴影偏移
    ui->portSet_Button->setGraphicsEffect(shadoweffect_02);

    //部件阴影效果
    QGraphicsDropShadowEffect *shadoweffect_03 = new QGraphicsDropShadowEffect;
    //阴影色, 透明度
    shadoweffect_03->setColor(QColor(100,100,100));
    shadoweffect_03->setBlurRadius(10);//阴影模糊半径
    shadoweffect_03->setOffset(5);    //阴影偏移
    ui->imageGetButton->setGraphicsEffect(shadoweffect_03);

    //部件阴影效果
    QGraphicsDropShadowEffect *shadoweffect_04 = new QGraphicsDropShadowEffect;
    //阴影色, 透明度
    shadoweffect_04->setColor(QColor(100,100,100));
    shadoweffect_04->setBlurRadius(10);//阴影模糊半径
    shadoweffect_04->setOffset(5);    //阴影偏移
    ui->lightAdjButton->setGraphicsEffect(shadoweffect_04);

    //部件阴影效果
    QGraphicsDropShadowEffect *shadoweffect_05 = new QGraphicsDropShadowEffect;
    //阴影色, 透明度
    shadoweffect_05->setColor(QColor(100,100,100));
    shadoweffect_05->setBlurRadius(10);//阴影模糊半径
    shadoweffect_05->setOffset(5);    //阴影偏移
    ui->sysSettingsButton->setGraphicsEffect(shadoweffect_05);

    //窗口显示在屏幕正中间
    QDesktopWidget *homePage = QApplication::desktop();
    move((homePage->width()-this->width())/2,(homePage->height()-this->height())/2);

    /*返回主页面*/
    connect(ui->exitButton,&QPushButton::clicked,[=](){emit back();});
    /*跳转至串口设置页面*/
    portSets = PortSettings::get_ins();
    connect(ui->portSet_Button,&QPushButton::clicked,[=](){portSets->show();});
    connect(portSets,&PortSettings::back,[=](){portSets->hide();});
    /*跳转至相机设置页面：page06_01 */
    //page06_01 = new Page06_1;
    //connect(ui->camSets_Button,&QPushButton::clicked,[=](){this->hide();page06_01->show();});
    //connect(page06_01,&Page06_1::back,[=](){page06_01->hide();this->show();});
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
