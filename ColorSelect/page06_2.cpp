#include "page06_2.h"
#include "ui_page06_2.h"

Page06_2::Page06_2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Page06_2)
{
    ui->setupUi(this);
    /*返回主页面*/
    connect(ui->exitButton,&QPushButton::clicked,[=](){emit back();});
    //******************写处理对象调用***********************
    writePro = writeProcess::get_ins();
    //******************界面显示***********************
    /*初始化显示*/
    setWindowTitle("恒流源板调节");
    /*亮度范围*/
    ui->ligDegree_spinBox->setRange(0,100);
    ui->ligDegree_spinBox->setValue(30);
    ui->ligDegree_spinBox->setSingleStep(5);
    /*颜色显示*/
    ui->color_comboBox->addItem("白光");
    ui->color_comboBox->addItem("绿光");
    ui->color_comboBox->addItem("蓝光");
    ui->color_comboBox->addItem("红光");
}

Page06_2::~Page06_2()
{
    delete ui;
}

void Page06_2::on_saveButton_clicked()
{
    /*亮度调节*/
    int dec = ui->ligDegree_spinBox->value();
    qDebug()<<"ligDegree:"<<dec;
    QString data1 = QString::number(dec, 16).toUpper();
    qDebug()<<"当前常规延时："<<data1;
    /*颜色调节*/
    int color = ui->color_comboBox->currentIndex();
    QString data2;
    switch(color)
    {
    case 0:
        //白光
        data2 = "00";
        break;
    case 1:
        //绿光
        data2 = "01";
        break;
    case 2:
        //蓝光
        data2 = "02";
        break;
    case 3:
        //红光
        data2 = "03";
        break;
    default:
        data2 = "00";
        break;
    }

    //发送指令
    writePro->sendCommand("02",data1,data2);
}
