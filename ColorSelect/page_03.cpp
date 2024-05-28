#include "page_03.h"
#include "ui_page_03.h"
#include <QTimer>
#include <QDesktopWidget>


Page_03::Page_03(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Page_03),timer(nullptr),
    inProgress(false)  // 初始化标志为 false
{
    ui->setupUi(this);
    //窗口显示在屏幕正中间
    QDesktopWidget *homePage = QApplication::desktop();
    move((homePage->width()-this->width())/2,(homePage->height()-this->height())/2);

    //喷阀多检使用定时器
    dec = 1;
    // 创建 QTimer
    timer = new QTimer(this);
    // 将 timeout 信号与 yourSlot 槽函数连接
    connect(timer, &QTimer::timeout, this, &Page_03::checkSlot);
    // 设置定时器的时间间隔为100ms
    timer->setInterval(700);

    this->setWindowTitle("气阀页面");
    /*返回主页面*/
    connect(ui->exitButton,&QPushButton::clicked,[=](){emit back();});
    //******************写处理对象调用***********************
    writePro = writeProcess::get_ins();
    readPro = readProcess::get_ins();
    //connect(readPro,&readProcess::data_Page_03,this,&Page_03::updateDisplay);
    //ui->lcdNumber->setDigitCount(4);
    //ui->lcdNumber->setSegmentStyle(QLCDNumber::Flat);
    //ui->pressure_spinBox->setRange(0,1000);
    //ui->pressure_spinBox->setSuffix(" KPa");

    //******************界面显示***********************
    /*常规延时*/
    ui->customDelay_spin->setRange(0,100);
    ui->customDelay_spin->setSuffix(" ms");
    ui->customDelay_spin->setValue(30);
    ui->customDelay_spin->setSingleStep(1);
    /*模型延时*/
    ui->modelDelay_spin->setRange(0,100);
    ui->modelDelay_spin->setSuffix(" ms");
    ui->modelDelay_spin->setValue(30);
    ui->modelDelay_spin->setSingleStep(1);
    /*重吹时间*/
    ui->reTime_spin->setRange(0,100);
    ui->reTime_spin->setSuffix(" ms");
    ui->reTime_spin->setValue(30);
    ui->reTime_spin->setSingleStep(1);
    /*吹气时间*/
    ui->time_spin->setRange(0,100);
    ui->time_spin->setSuffix(" ms");
    ui->time_spin->setValue(30);
    ui->time_spin->setSingleStep(1);
    //喷阀检测次序
    ui->airvalve_spin->setRange(1,64);
    ui->airvalve_spin->setSingleStep(1);
    //喷阀自检
    ui->multiChe_Button->setText("快速自检");
}

Page_03::~Page_03()
{
    delete ui;
}

/*
 * 函数：updateDisplay()
 * 参数：data
 * 功能：当前气压回传显示刷新
 * 备注：
 */
//void Page_03::updateDisplay(const QByteArray &data)
//{
//    QByteArray receData = data;
//    if(receData.size() >= 3){
//        quint8 highByte = static_cast<quint8>(receData.at(1));
//        quint8 lowByte = static_cast<quint8>(receData.at(2));

//        quint16 result = (static_cast<quint16>(highByte) << 8) | lowByte;
//        //ui->pressure_spinBox->setValue(result);

//        ui->lcdNumber->display(result);

//        qDebug()<<"receData:"<<receData;
//        qDebug()<<"result:"<<result;
//    }
//}

/*
 * 函数：on_singleChe_Button_clicked()
 * 参数：
 * 功能：喷阀单检
 * 备注：
 */
void Page_03::on_singleChe_Button_clicked()
{
    //喷阀逐个检测
    int dec = ui->airvalve_spin->value();
    qDebug()<<"检测气阀:"<<dec;
    QString data2 = QString::number(dec, 16).toUpper();
    writePro->sendCommand("0b","00",data2);
}

/*
 * 函数：checkSlot()
 * 参数：
 * 功能：喷阀多检工作槽函数
 * 备注：
 */
void Page_03::checkSlot()
{
    // 执行相关逻辑
    QString data2 = QString::number(dec, 16).toUpper();
    qDebug() << "正在检测第" << dec << "个气阀！";
    ui->airvalve_spin->setValue(dec);
    writePro->sendCommand("0b", "00", data2);

    // 判断是否已经执行到 dec = 64，如果是则停止定时器
    if (dec == 64)
    {
        timer->stop();
    }
    else
    {
        // 否则递增 dec，并重新启动定时器
        dec++;
        timer->start();
    }
}


/*
 * 函数：on_multiChe_Button_clicked()
 * 参数：
 * 功能：喷阀多检启动槽函数
 * 备注：
 */
void Page_03::on_multiChe_Button_clicked()
{
    if(ui->multiChe_Button->text() == "快速自检")
    {
        // 重置 dec 的值
        dec = 1;

        // 启动定时器
        timer->start();
        ui->multiChe_Button->setText("停止检测");
    }
    else
    {
        timer->stop();
        ui->multiChe_Button->setText("快速自检");
    }

}



/*
 * 函数：on_saveButton_clicked()
 * 参数：
 * 功能：保存数值调节
 * 备注：发送第四条指令时会显示当前系统时间问题
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
