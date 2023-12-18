#include "page_03.h"
#include "ui_page_03.h"

Page_03::Page_03(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Page_03)
{
    ui->setupUi(this);
    this->setWindowTitle("气阀页面");
    /*返回主页面*/
    connect(ui->exitButton,&QPushButton::clicked,[=](){emit back();});
    //******************写处理对象调用***********************
    writePro = writeProcess::get_ins();
    //******************界面显示***********************
    /*常规延时*/
    ui->customDelay_spin->setRange(0,100);
    ui->customDelay_spin->setSuffix("ms");
    ui->customDelay_spin->setValue(30);
    ui->customDelay_spin->setSingleStep(1);
    /*模型延时*/
    ui->modelDelay_spin->setRange(0,100);
    ui->modelDelay_spin->setSuffix("ms");
    ui->modelDelay_spin->setValue(30);
    ui->modelDelay_spin->setSingleStep(1);
    /*重吹时间*/
    ui->reTime_spin->setRange(0,100);
    ui->reTime_spin->setSuffix("ms");
    ui->reTime_spin->setValue(30);
    ui->reTime_spin->setSingleStep(1);
    /*吹气时间*/
    ui->time_spin->setRange(0,100);
    ui->time_spin->setSuffix("ms");
    ui->time_spin->setValue(30);
    ui->time_spin->setSingleStep(1);
}

Page_03::~Page_03()
{
    delete ui;
}

/*
 * 函数：on_singleChe_Button_clicked()
 * 参数：
 * 功能：喷阀单检
 * 备注：暂未设定如何选中检测目标
 */
void Page_03::on_singleChe_Button_clicked()
{
    //喷阀逐个检测
    writePro->sendCommand("0b","00","01");
}

/*
 * 函数：on_multiChe_Button_clicked()
 * 参数：
 * 功能：喷阀多检
 * 备注：暂不需要该功能
 */
void Page_03::on_multiChe_Button_clicked()
{
//    //喷阀逐个检测
//    writePro->sendCommand("0c","00","01");
//    //指示灯逐个检测
//    writePro->sendCommand("0c","00","02");
}

/*
 * 函数：on_saveButton_clicked()
 * 参数：
 * 功能：保存数值调节
 * 备注：发送第四条指令时会显示当前系统时间
 */
void Page_03::on_saveButton_clicked()
{
    /*常规延时*/
    int dec_1 = ui->customDelay_spin->value();
    qDebug()<<"customDelay:"<<dec_1;
    QString data2_1 = QString::number(dec_1, 16).toUpper();
    qDebug()<<"当前常规延时："<<data2_1;
    //发送常规延时修改指令
    writePro->sendCommand("07","00",data2_1);
    /*模型延时*/
    int dec_2 = ui->modelDelay_spin->value();
    qDebug()<<"modelDelay:"<<dec_2;
    QString data2_2 = QString::number(dec_2, 16).toUpper();
    qDebug()<<"当前模型延时："<<data2_2;
    //发送模型延时修改指令
    writePro->sendCommand("08","00",data2_2);
    /*重吹时间*/
    int dec_3 = ui->reTime_spin->value();
    qDebug()<<"reTime:"<<dec_3;
    QString data2_3 = QString::number(dec_3, 16).toUpper();
    qDebug()<<"当前重吹时间："<<data2_3;
    //发送重吹时间修改指令
    writePro->sendCommand("09","00",data2_3);
    /*吹气时间*/
    int dec_4 = ui->time_spin->value();
    qDebug()<<"time:"<<dec_4;
    QString data2_4 = QString::number(dec_4, 16).toUpper();
    qDebug()<<"当前吹气时间："<<data2_4;
    //发送吹气时间修改指令
    writePro->sendCommand("0a","00",data2_4);
}
