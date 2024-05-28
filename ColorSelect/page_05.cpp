#include "page_05.h"
#include "ui_page_05.h"
#include <QDesktopWidget>

Page_05::Page_05(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Page_05)
{
    ui->setupUi(this);
    this->setWindowTitle("模型页面");

    //窗口显示在屏幕正中间
    QDesktopWidget *homePage = QApplication::desktop();
    move((homePage->width()-this->width())/2,(homePage->height()-this->height())/2);

    /*返回主页面*/
    connect(ui->exitButton,&QPushButton::clicked,[=](){emit back();});
    //******************写处理对象调用***********************
    writePro = writeProcess::get_ins();
    readPro = readProcess::get_ins();

    //******************界面显示***********************
    connect(readPro,&readProcess::data_Page_05,this,&Page_05::updateDisplay);
    ui->pressure_spinBox->setRange(0,1000);
    ui->pressure_spinBox->setSuffix(" KPa");
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
    qDebug()<<"切换为第一种模型";
}

/*
 * 函数：updateDisplay()
 * 参数：data
 * 功能：当前气压回传显示刷新
 * 备注：
 */
void Page_05::updateDisplay(const QByteArray &data)
{
    QByteArray receData = data;
    if(receData.size() >= 3){
        quint8 highByte = static_cast<quint8>(receData.at(1));
        quint8 lowByte = static_cast<quint8>(receData.at(2));

        quint16 result = (static_cast<quint16>(highByte) << 8) | lowByte;
        ui->pressure_spinBox->setValue(result);

        qDebug()<<"receData:"<<receData;
        qDebug()<<"result:"<<result;
    }
}
