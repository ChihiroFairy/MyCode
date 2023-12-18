#ifndef PAGE_01_H
#define PAGE_01_H

#include <QWidget>
#include "writeprocess.h"

namespace Ui {
class Page_01;
}

class Page_01 : public QWidget
{
    Q_OBJECT

public:
    explicit Page_01(QWidget *parent = nullptr);
    ~Page_01();

signals:
    void back();

private:
    Ui::Page_01 *ui;
    //创建 写_预处理 对象
    writeProcess *writePro;
};

#endif // PAGE_01_H
