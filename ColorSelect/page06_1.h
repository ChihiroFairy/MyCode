#ifndef PAGE06_1_H
#define PAGE06_1_H

#include <QWidget>
#include "writeprocess.h"

namespace Ui {
class Page06_1;
}

class Page06_1 : public QWidget
{
    Q_OBJECT

public:
    explicit Page06_1(QWidget *parent = nullptr);
    ~Page06_1();

signals:
    void back();

private slots:
    void on_cam_listWidget_currentRowChanged(int currentRow);

    void on_saveButton_clicked();

private:
    Ui::Page06_1 *ui;
    //保存参数设置函数
    void saveSettings();
    //创建 写_预处理 对象
    writeProcess *writePro;
};

#endif // PAGE06_1_H
