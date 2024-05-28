#include "homepage.h"
#include "ui_homepage.h"
#include <QGraphicsDropShadowEffect>
#include <QDesktopWidget>

HomePage::HomePage(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::HomePage)
{
    ui->setupUi(this);

    this->setWindowTitle("主界面");

    //窗口显示在屏幕正中间
    QDesktopWidget *homePage = QApplication::desktop();
    move((homePage->width()-this->width())/2,(homePage->height()-this->height())/2);

    /*图标显示*/
    //部件阴影效果
    QGraphicsDropShadowEffect *shadoweffect_00 = new QGraphicsDropShadowEffect;
    //阴影色, 透明度
    shadoweffect_00->setColor(QColor(100,100,100));
    shadoweffect_00->setBlurRadius(10);//阴影模糊半径
    shadoweffect_00->setOffset(5);    //阴影偏移
    ui->openButton->setGraphicsEffect(shadoweffect_00);

    QGraphicsDropShadowEffect *shadoweffect_11 = new QGraphicsDropShadowEffect;
    //阴影色, 透明度
    shadoweffect_11->setColor(QColor(100,100,100));
    shadoweffect_11->setBlurRadius(10);//阴影模糊半径
    shadoweffect_11->setOffset(5);    //阴影偏移
    ui->closeButton->setGraphicsEffect(shadoweffect_11);

    QGraphicsDropShadowEffect *shadoweffect_1 = new QGraphicsDropShadowEffect;
    //阴影色, 透明度
    shadoweffect_1->setColor(QColor(100,100,100));
    shadoweffect_1->setBlurRadius(10);//阴影模糊半径
    shadoweffect_1->setOffset(3);    //阴影偏移
    ui->page01_Button->setGraphicsEffect(shadoweffect_1);

    QGraphicsDropShadowEffect *shadoweffect_2 = new QGraphicsDropShadowEffect;
    //阴影色, 透明度
    shadoweffect_2->setColor(QColor(100,100,100));
    shadoweffect_2->setBlurRadius(10);//阴影模糊半径
    shadoweffect_2->setOffset(3);    //阴影偏移
    ui->page02_Button->setGraphicsEffect(shadoweffect_2);

    QGraphicsDropShadowEffect *shadoweffect_3 = new QGraphicsDropShadowEffect;
    //阴影色, 透明度
    shadoweffect_3->setColor(QColor(100,100,100));
    shadoweffect_3->setBlurRadius(10);//阴影模糊半径
    shadoweffect_3->setOffset(3);    //阴影偏移
    ui->page03_Button->setGraphicsEffect(shadoweffect_3);

    QGraphicsDropShadowEffect *shadoweffect_4 = new QGraphicsDropShadowEffect;
    //阴影色, 透明度
    shadoweffect_4->setColor(QColor(100,100,100));
    shadoweffect_4->setBlurRadius(10);//阴影模糊半径
    shadoweffect_4->setOffset(3);    //阴影偏移
    ui->page04_Button->setGraphicsEffect(shadoweffect_4);

    QGraphicsDropShadowEffect *shadoweffect_5 = new QGraphicsDropShadowEffect;
    //阴影色, 透明度
    shadoweffect_5->setColor(QColor(100,100,100));
    shadoweffect_5->setBlurRadius(10);//阴影模糊半径
    shadoweffect_5->setOffset(3);    //阴影偏移
    ui->page05_Button->setGraphicsEffect(shadoweffect_5);

    QGraphicsDropShadowEffect *shadoweffect_6 = new QGraphicsDropShadowEffect;
    //阴影色, 透明度
    shadoweffect_6->setColor(QColor(100,100,100));
    shadoweffect_6->setBlurRadius(10);//阴影模糊半径
    shadoweffect_6->setOffset(3);    //阴影偏移
    ui->page06_Button->setGraphicsEffect(shadoweffect_6);

     /*跳转至下料页面：pageOpen */
    pageOpen = new PageOpen;
    connect(ui->openButton,&QPushButton::clicked,[=](){pageOpen->show();});
    connect(pageOpen,&PageOpen::back,[=](){pageOpen->hide();});
    /*跳转至关机页面:pageClose */
    pageClose = new PageClose;
    connect(ui->closeButton,&QPushButton::clicked,[=](){pageClose->show();});
    connect(pageClose,&PageClose::back,[=](){pageClose->hide();});
    /*跳转至精度页面 :Page_01*/
    page01 = new Page_01;
    connect(ui->page01_Button,&QPushButton::clicked,[=](){this->hide();page01->show();});
    connect(page01,&Page_01::back,[=](){page01->hide();this->show();});

    //******************页面跳转连接********************************
    /*跳转至产量页面 :Page_02*/
    page02 = new Page_02;
    connect(ui->page02_Button,&QPushButton::clicked,[=](){this->hide();page02->show();});
    connect(page02,&Page_02::back,[=](){page02->hide();this->show();});
    /*跳转至气阀页面 :Page_03*/
    page03 = new Page_03;
    connect(ui->page03_Button,&QPushButton::clicked,[=](){this->hide();page03->show();});
    connect(page03,&Page_03::back,[=](){page03->hide();this->show();});
    /*跳转至流阿量页面 :Page_04*/
    page04 = new Page_04;
    connect(ui->page04_Button,&QPushButton::clicked,[=](){this->hide();page04->show();});
    connect(page04,&Page_04::back,[=](){page04->hide();this->show();});
    /*跳转至模型页面 :Page_05*/
    page05 = new Page_05;
    connect(ui->page05_Button,&QPushButton::clicked,[=](){this->hide();page05->show();});
    connect(page05,&Page_05::back,[=](){page05->hide();this->show();});
    /*跳转至设置页面 :Page_06*/
    page06 = new Page_06;
    connect(ui->page06_Button,&QPushButton::clicked,[=](){this->hide();page06->show();});
    connect(page06,&Page_06::back,[=](){page06->hide();this->show();});
}

HomePage::~HomePage()
{
    delete ui;
    delete pageOpen;
    delete pageClose;
    delete page01;
    delete page02;
    delete page03;
    delete page04;
    delete page05;
    delete page06;
}

