#include "page06_1.h"
#include "ui_page06_1.h"

Page06_1::Page06_1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Page06_1)
{
    ui->setupUi(this);
    /*返回主页面*/
    connect(ui->exitButton,&QPushButton::clicked,[=](){emit back();});
    //******************写处理对象调用***********************
    writePro = writeProcess::get_ins();
    //******************界面显示***********************
    /*初始化显示*/
    setWindowTitle("前主相机");
    /*前主相机*/
    /*分辨率*/
    ui->reso_comboBox_qz->addItem("1024");
    ui->reso_comboBox_qz->addItem("512");
    ui->reso_comboBox_qz->addItem("2048");
    ui->reso_comboBox_qz->setCurrentIndex(0);
    /*维度*/
    ui->demen_comboBox_qz->addItem("1维");
    ui->demen_comboBox_qz->addItem("2维");
    ui->demen_comboBox_qz->addItem("3维");
    ui->demen_comboBox_qz->setCurrentIndex(0);
    /*帧频*/
    ui->fraFreque_comboBox_qz->addItem("0.5");
    ui->fraFreque_comboBox_qz->addItem("1");
    ui->fraFreque_comboBox_qz->addItem("2");
    ui->fraFreque_comboBox_qz->addItem("2.5");
    ui->fraFreque_comboBox_qz->addItem("2.8");
    ui->fraFreque_comboBox_qz->addItem("3");
    ui->fraFreque_comboBox_qz->setCurrentIndex(0);
    /*镜像*/
    ui->mirror_comboBox_qz->addItem("否");
    ui->mirror_comboBox_qz->addItem("是");
    ui->mirror_comboBox_qz->setCurrentIndex(0);
    /*后主相机*/
    /*分辨率*/
    ui->reso_comboBox_hz->addItem("1024");
    ui->reso_comboBox_hz->addItem("512");
    ui->reso_comboBox_hz->addItem("2048");
    ui->reso_comboBox_hz->setCurrentIndex(0);
    /*维度*/
    ui->demen_comboBox_hz->addItem("1维");
    ui->demen_comboBox_hz->addItem("2维");
    ui->demen_comboBox_hz->addItem("3维");
    ui->demen_comboBox_hz->setCurrentIndex(0);
    /*帧频*/
    ui->fraFreque_comboBox_hz->addItem("0.5");
    ui->fraFreque_comboBox_hz->addItem("1");
    ui->fraFreque_comboBox_hz->addItem("2");
    ui->fraFreque_comboBox_hz->addItem("2.5");
    ui->fraFreque_comboBox_hz->addItem("2.8");
    ui->fraFreque_comboBox_hz->addItem("3");
    ui->fraFreque_comboBox_hz->setCurrentIndex(0);
    /*镜像*/
    ui->mirror_comboBox_hz->addItem("否");
    ui->mirror_comboBox_hz->addItem("是");
    ui->mirror_comboBox_hz->setCurrentIndex(0);
}

Page06_1::~Page06_1()
{
    delete ui;
}

/*
 * 函数：on_cam_listWidget_currentRowChangedd()
 * 参数：
 * 功能：切换前主/后主相机设置页面
 * 备注：
 */
void Page06_1::on_cam_listWidget_currentRowChanged(int currentRow)
{
    //切换前后相机设置页面
    ui->page->setCurrentIndex(currentRow);
    switch(currentRow)
    {
    case 0:
        setWindowTitle("前主相机");
        break;
    case 1:
        setWindowTitle("后主相机");
        break;
    default:
        setWindowTitle("前主相机");
        break;
    }
}

/*
 * 函数：on_saveButton_clicked()
 * 参数：
 * 功能：保存参数设置
 * 备注：
 */
void Page06_1::on_saveButton_clicked()
{
    saveSettings();
}
void Page06_1::saveSettings()
{
    /*前主相机*/
    /*分辨率*/
    int res_qz = ui->reso_comboBox_qz->currentIndex();
    switch(res_qz){
    case 0:
        //分辨率：1024
        writePro->sendCommand("23","04","00");
        break;
    case 1:
        //分辨率：512
        writePro->sendCommand("23","02","00");
        break;
    case 2:
        //分辨率：2048
        writePro->sendCommand("23","08","00");
        break;
    default:
        //分辨率：1024
        writePro->sendCommand("23","04","00");
        break;
    }
    /*维度*/
    int dims_qz = ui->demen_comboBox_qz->currentIndex();
    switch(dims_qz)
    {
    case 0:
        //1维
        writePro->sendCommand("24","00","01");
        break;
    case 1:
        //2维
        writePro->sendCommand("24","00","02");
        break;
    case 2:
        //3维
        writePro->sendCommand("24","00","03");
        break;
    default:
        //1维
        writePro->sendCommand("24","00","01");
        break;
    }
    /*帧频*/
    int fraFre_qz = ui->fraFreque_comboBox_qz->currentIndex();
    switch(fraFre_qz)
    {
    case 0:
        //0.5
        writePro->sendCommand("26","00","01");
        break;
    case 1:
        //1
        writePro->sendCommand("26","00","02");
        break;
    case 2:
        //2
        writePro->sendCommand("26","00","03");
        break;
    case 3:
        //2.5
        writePro->sendCommand("26","00","04");
        break;
    case 4:
        //2.8
        writePro->sendCommand("26","00","05");
        break;
    case 5:
        //3
        writePro->sendCommand("26","00","06");
        break;
    default:
        writePro->sendCommand("26","00","01");
        break;
    }
    /*镜像*/
    int mir_qz = ui->mirror_comboBox_qz->currentIndex();
    switch(mir_qz)
    {
    case 0:
        //镜像：否
        writePro->sendCommand("29","00","00");
        break;
    case 1:
        //镜像：是
        writePro->sendCommand("29","00","01");
        break;
    default:
        writePro->sendCommand("29","00","00");
        break;
    }
    /*后主相机*/
    /*分辨率*/
    int res_hz = ui->reso_comboBox_hz->currentIndex();
    switch(res_hz){
    case 0:
        //分辨率：1024
        writePro->sendCommand("23","04","00");
        break;
    case 1:
        //分辨率：512
        writePro->sendCommand("23","02","00");
        break;
    case 2:
        //分辨率：2048
        writePro->sendCommand("23","08","00");
        break;
    default:
        //分辨率：1024
        writePro->sendCommand("23","04","00");
        break;
    }
    /*维度*/
    int dims_hz = ui->demen_comboBox_hz->currentIndex();
    switch(dims_hz)
    {
    case 0:
        //1维
        writePro->sendCommand("24","00","01");
        break;
    case 1:
        //2维
        writePro->sendCommand("24","00","02");
        break;
    case 2:
        //3维
        writePro->sendCommand("24","00","03");
        break;
    default:
        //1维
        writePro->sendCommand("24","00","01");
        break;
    }
    /*帧频*/
    int fraFre_hz = ui->fraFreque_comboBox_hz->currentIndex();
    switch(fraFre_hz)
    {
    case 0:
        //0.5
        writePro->sendCommand("26","00","01");
        break;
    case 1:
        //1
        writePro->sendCommand("26","00","02");
        break;
    case 2:
        //2
        writePro->sendCommand("26","00","03");
        break;
    case 3:
        //2.5
        writePro->sendCommand("26","00","04");
        break;
    case 4:
        //2.8
        writePro->sendCommand("26","00","05");
        break;
    case 5:
        //3
        writePro->sendCommand("26","00","06");
        break;
    default:
        writePro->sendCommand("26","00","01");
        break;
    }
    /*镜像*/
    int mir_hz = ui->mirror_comboBox_hz->currentIndex();
    switch(mir_hz)
    {
    case 0:
        //镜像：否
        writePro->sendCommand("29","00","00");
        break;
    case 1:
        //镜像：是
        writePro->sendCommand("29","00","01");
        break;
    default:
        writePro->sendCommand("29","00","00");
        break;
    }
}
