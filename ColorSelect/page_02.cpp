#include "page_02.h"
#include "ui_page_02.h"

Page_02::Page_02(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Page_02)
{
    ui->setupUi(this);

    this->setWindowTitle("流量页面");
    /*返回主页面*/
    connect(ui->exitButton,&QPushButton::clicked,[=](){emit back();});
    //******************写处理对象调用***********************
    writePro = writeProcess::get_ins();
    //******************界面显示***********************
    /*传送带*/
    //传送带速度调节范围为0-10
    ui->speedAdj_DoubleSpinBox->setRange(0,10);
    //当前值为3
    ui->speedAdj_DoubleSpinBox->setValue(3);
    ui->speedAdj_DoubleSpinBox->setSingleStep(0.1);
    ui->speedAdj_DoubleSpinBox->setSuffix("m/s");

    /*振动器*/
    ui->vibratorButton->setText("振动器已关闭！");
    //振动器振动量调节范围为1-100
    ui->vibratorAdj_spinBox->setRange(1,100);
    //单步调节值为1
    ui->vibratorAdj_spinBox->setSingleStep(1);
    ui->vibratorAdj_spinBox->setEnabled(false);
}

Page_02::~Page_02()
{
    delete ui;
}

/*
 * 函数：on_vibratorButton_stateChanged()
 * 参数：arg1
 * 功能：控制振动器开关
 * 备注：初始状态为关
 */
void Page_02::on_vibratorButton_stateChanged(int arg1)
{
    if(arg1 == 0){
        //初始为unchecked状态
       writePro->sendCommand("03","00","00");
       ui->vibratorAdj_spinBox->setEnabled(false);
       ui->vibratorButton->setText("振动器已关闭！");
    }
    else{
        //点击后为checked状态
       writePro->sendCommand("03","00","aa");
       ui->vibratorAdj_spinBox->setEnabled(true);
       //当前值为30
       ui->vibratorAdj_spinBox->setValue(30);
       ui->vibratorButton->setText("振动器已打开！");
    }
}

/*
 * 函数：on_vibratorAdj_spinBox_valueChanged()
 * 参数：arg1
 * 功能：实时振动量调节
 * 备注：在振动器打开条件下执行该函数
 */
void Page_02::on_vibratorAdj_spinBox_valueChanged(const QString &arg1)
{
    //将当前文本框的值转换为十六进制
    QString data2 = QString::number(arg1.toInt(), 16).toUpper();
    qDebug()<<"测试转换结果振动量："<<data2;
    //发送振动量修改指令
    writePro->sendCommand("03","00",data2);
}

/*
 * 函数：on_speedAdj_DoubleSpinBox_valueChanged()
 * 参数：arg1
 * 功能：实时传送带速度调节
 * 备注：
 * note:传送带速度初始值为30，暂时无法在开机时自动发送指令
 */
void Page_02::on_speedAdj_DoubleSpinBox_valueChanged(const double &arg1)
{
    // 将浮点数转换为整数
    int temp = static_cast<int>(arg1 * 10);

    // 将整数转换为十六进制字符串
    QString data2 = QString::number(temp, 16).toUpper();
    qDebug()<<"data1:"<<data2.toUpper();
    // 发送振动量修改指令
    writePro->sendCommand("04", "00", data2);
}
