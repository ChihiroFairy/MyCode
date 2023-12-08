#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "serialport.h"
#include "preproccess.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class device02;
class preproccess;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:

private slots:
    void on_sendButton_clicked();
    void upDateDisplay(const QByteArray &data);

private:
    Ui::MainWindow *ui;
    //串口参数配置对象
    portSettings *portSetting;
    // 创建 device02 类的实例
    device02 *dev02;
    preproccess *prePross;
};
#endif // MAINWINDOW_H
