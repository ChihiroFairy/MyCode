#ifndef PAGE_02_H
#define PAGE_02_H

#include <QWidget>
#include "writeprocess.h"
#include "readprocess.h"

namespace Ui {
class Page_02;
}

class Page_02 : public QWidget
{
    Q_OBJECT

public:
    explicit Page_02(QWidget *parent = nullptr);
    ~Page_02();

signals:
    void back();

private slots:
    //振动器打开与关闭
    void on_vibratorButton_stateChanged(int arg1);

    void on_vibratorAdj_spinBox_valueChanged(const QString &arg1);

    void on_speedAdj_DoubleSpinBox_valueChanged(const double &arg1);

private:
    Ui::Page_02 *ui;
    //创建 写_预处理 对象
    writeProcess *writePro;
};

#endif // PAGE_02_H
