#ifndef PAGE_05_H
#define PAGE_05_H

#include <QWidget>
#include "writeprocess.h"

namespace Ui {
class Page_05;
}

class Page_05 : public QWidget
{
    Q_OBJECT

public:
    explicit Page_05(QWidget *parent = nullptr);
    ~Page_05();

signals:
    void back();

private slots:
    void on_changeButton_clicked();

private:
    Ui::Page_05 *ui;
    //创建 写_预处理 对象
    writeProcess *writePro;
};

#endif // PAGE_05_H
