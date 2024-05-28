#include "page_04.h"
#include "ui_page_04.h"
#include <QDesktopWidget>

Page_04::Page_04(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Page_04)
{
    ui->setupUi(this);
    this->setWindowTitle("清灰页面");

    //窗口显示在屏幕正中间
    QDesktopWidget *homePage = QApplication::desktop();
    move((homePage->width()-this->width())/2,(homePage->height()-this->height())/2);

    /*返回主页面*/
    connect(ui->exitButton,&QPushButton::clicked,[=](){emit back();});
    //******************写处理对象调用***********************
    writePro = writeProcess::get_ins();
    //******************界面显示***********************
    /*清灰间隔*/
    ui->interval_spinBox->setRange(1,1024);
    ui->interval_spinBox->setSuffix(" mins");
    ui->interval_spinBox->setValue(512);
    ui->interval_spinBox->setSingleStep(5);
    /*清灰周期*/
    ui->cycle_spinBox->setRange(0,64);
    ui->cycle_spinBox->setSuffix(" s");
    ui->cycle_spinBox->setValue(30);
    ui->cycle_spinBox->setSingleStep(1);
}

Page_04::~Page_04()
{
    delete ui;
}

/*
 * 函数：on_autoClean_Button_clicked()
 * 参数：
 * 功能：定时清灰
 * 备注：
 * note：发送512对应指令时串口助手会显示当前系统时间问题
 */
void Page_04::on_autoClean_Button_clicked()
{
    //将当前文本框的值转换为十六进制
    int dec = ui->interval_spinBox->value();
    QString hex = QString("%1").arg(dec, 4, 16, QChar('0')).toUpper();
    qDebug()<<"测试转换结果清灰："<<hex;
    //高八位
    QString data1 = hex.mid(0,2);
    //低八位
    QString data2 = hex.mid(2,2);

    //发送振动量修改指令
    writePro->sendCommand("05",data1,data2);
}

/*
 * 函数：on_manualClean_Button_clicked()
 * 参数：
 * 功能：手动清灰
 * 备注：
 */
void Page_04::on_manualClean_Button_clicked()
{
    //将当前文本框的值转换为十六进制
    int dec = ui->cycle_spinBox->value();
    QString data2 = QString::number(dec, 16).toUpper();
    qDebug()<<"进行手动清灰，"<<"清灰周期："<<dec;
    //发送振动量修改指令
    writePro->sendCommand("06","00",data2);
}
