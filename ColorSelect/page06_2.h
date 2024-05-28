#ifndef PAGE06_2_H
#define PAGE06_2_H

#include <QWidget>
#include "writeprocess.h"

namespace Ui {
class Page06_2;
}

class Page06_2 : public QWidget
{
    Q_OBJECT

public:
    explicit Page06_2(QWidget *parent = nullptr);
    ~Page06_2();

signals:
    void back();

private slots:
    void on_saveButton_clicked();

    void on_redButton_clicked();

    void on_greenButton_clicked();

    void on_blueButton_clicked();

    void on_warningButton_clicked();

    int on_color_comboBox_currentIndexChanged(int index);

private:
    Ui::Page06_2 *ui;
    //创建 写_预处理 对象
    writeProcess *writePro;

    bool red;
    bool yellow;
    bool green;
};

#endif // PAGE06_2_H
