#include "page06_2.h"
#include "ui_page06_2.h"
#include <QDesktopWidget>

Page06_2::Page06_2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Page06_2)
{
    ui->setupUi(this);

    //窗口显示在屏幕正中间
    QDesktopWidget *homePage = QApplication::desktop();
    move((homePage->width()-this->width())/2,(homePage->height()-this->height())/2);

    /*返回主页面*/
    connect(ui->exitButton,&QPushButton::clicked,[=](){emit back();});
    //******************写处理对象调用***********************
    writePro = writeProcess::get_ins();
    //******************界面显示***********************
    /*初始化显示*/
    setWindowTitle("恒流源板调节");
    /*亮度范围*/
    ui->ligDegree_spinBox_fir_white->setRange(0,100);
    ui->ligDegree_spinBox_fir_white->setValue(30);
    ui->ligDegree_spinBox_fir_white->setSingleStep(5);
    ui->ligDegree_spinBox_fir_white->setSuffix(" %");

    ui->ligDegree_spinBox_sec_white->setRange(0,100);
    ui->ligDegree_spinBox_sec_white->setValue(30);
    ui->ligDegree_spinBox_sec_white->setSingleStep(5);
    ui->ligDegree_spinBox_sec_white->setSuffix(" %");

    ui->ligDegree_spinBox_center_white->setRange(0,100);
    ui->ligDegree_spinBox_center_white->setValue(30);
    ui->ligDegree_spinBox_center_white->setSingleStep(5);
    ui->ligDegree_spinBox_center_white->setSuffix(" %");

    ui->ligDegree_spinBox_center_blue->setRange(0,100);
    ui->ligDegree_spinBox_center_blue->setValue(30);
    ui->ligDegree_spinBox_center_blue->setSingleStep(5);
    ui->ligDegree_spinBox_center_blue->setSuffix(" %");

    ui->ligDegree_spinBox_purple->setRange(0,100);
    ui->ligDegree_spinBox_purple->setValue(30);
    ui->ligDegree_spinBox_purple->setSingleStep(5);
    ui->ligDegree_spinBox_purple->setSuffix(" %");

    /*颜色显示*/
    ui->color_comboBox->addItem("1路白光");
    ui->color_comboBox->addItem("2路白光");
    ui->color_comboBox->addItem("中路白光");
    ui->color_comboBox->addItem("中路蓝光");
    ui->color_comboBox->addItem("紫光");
    /*声光报警显示*/

    red = false;
    yellow =false;
    green = false;

    ui->redButton->setText("红灯");
    ui->greenButton->setText("黄灯");
    ui->blueButton->setText("绿灯");
}

Page06_2::~Page06_2()
{
    delete ui;
}

void Page06_2::on_saveButton_clicked()
{
    /*亮度调节*/
    int dec;
    QString data1;
    switch(ui->tabWidget->currentIndex())
    {
    case 0:
        //1路白光
        dec = ui->ligDegree_spinBox_fir_white->value();
        data1 = QString::number(dec, 16).toUpper();
        break;
    case 1:
        //2路白光
        dec = ui->ligDegree_spinBox_sec_white->value();
        data1 = QString::number(dec, 16).toUpper();
        break;
    case 2:
        //中路白光
        dec = ui->ligDegree_spinBox_center_white->value();
        data1 = QString::number(dec, 16).toUpper();
        break;
    case 3:
        //中路蓝光
        dec = ui->ligDegree_spinBox_center_blue->value();
        data1 = QString::number(dec, 16).toUpper();
        break;
    case 4:
        //紫光
        dec = ui->ligDegree_spinBox_purple->value();
        data1 = QString::number(dec, 16).toUpper();
        break;
    default:
        //1路白光
        dec = ui->ligDegree_spinBox_fir_white->value();
        data1 = QString::number(dec, 16).toUpper();
        break;
    }

    /*颜色调节*/
    QString data2;
    int color = ui->color_comboBox->currentIndex();
    switch(color)
    {
    case 0:
        //1路白光
        data2 = "00";
        qDebug()<<"1路白光亮度调节至"<< dec << "%";
        break;
    case 1:
        //2路白光
        data2 = "01";
        qDebug()<<"2路白光亮度调节至"<< dec << "%";
        break;
    case 2:
        //中路白光
        data2 = "02";
        qDebug()<<"中路白光亮度调节至"<< dec << "%";
        break;
    case 3:
        //中路蓝光
        data2 = "03";
        qDebug()<<"中路蓝光亮度调节至"<< dec << "%";
        break;
    case 4:
        //紫光
        data2 = "02";
        writePro->sendCommand("02",data1,data2);
        data2 = "03";
        qDebug()<<"紫光亮度调节至"<< dec << "%";
        break;
    default:
        data2 = "00";
        break;
    }

    //发送指令
    writePro->sendCommand("02",data1,data2);
}

/*
 * 函数：声光报警测试（以下四个函数）
 * 参数：
 * 功能：声光报警
 * 备注：
 */
void Page06_2::on_redButton_clicked()
{
    if(!red){
        //发送指令
        writePro->sendCommand("11","00","00");
        ui->statusLabel->setText("状态：红色灯光闪烁!");
        red = true;
    }
    else{
        //发送指令
        writePro->sendCommand("11","00","00");
        ui->statusLabel->setText("状态：工作正常!");
        red = false;
    }
}
void Page06_2::on_greenButton_clicked()
{
    if(!yellow){
        //发送指令
        writePro->sendCommand("12","00","00");
        ui->statusLabel->setText("状态：黄色灯光闪烁!");
        yellow = true;
    }
    else{
        //发送指令
        writePro->sendCommand("12","00","00");
        ui->statusLabel->setText("状态：工作正常!");
        yellow = false;
    }
}

void Page06_2::on_blueButton_clicked()
{
    if(!green){
        //发送指令
        writePro->sendCommand("13","00","00");
        ui->statusLabel->setText("状态：绿色灯光闪烁!");
        green = true;
    }
    else{
        //发送指令
        writePro->sendCommand("13","00","00");
        ui->statusLabel->setText("状态：工作正常!");
        green = false;
    }
}
void Page06_2::on_warningButton_clicked()
{
    //发送指令
    writePro->sendCommand("14","00","00");
    ui->statusLabel->setText("状态：声光报警!");
}

//切换当前灯对应的亮度调节框
int Page06_2::on_color_comboBox_currentIndexChanged(int index)
{
    ui->tabWidget->setCurrentIndex(index);
    return index;
}
