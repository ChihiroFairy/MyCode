#include "homepage.h"
#include "ui_homepage.h"

HomePage::HomePage(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::HomePage)
{
    ui->setupUi(this);

    this->setWindowTitle("主界面");

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
    //******************图标样式设置********************************
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

