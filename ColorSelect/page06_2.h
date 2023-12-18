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

private:
    Ui::Page06_2 *ui;
    //创建 写_预处理 对象
    writeProcess *writePro;
};

#endif // PAGE06_2_H
