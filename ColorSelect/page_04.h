#ifndef PAGE_04_H
#define PAGE_04_H

#include <QWidget>
#include "writeprocess.h"
#include "readprocess.h"

namespace Ui {
class Page_04;
}

class Page_04 : public QWidget
{
    Q_OBJECT

public:
    explicit Page_04(QWidget *parent = nullptr);
    ~Page_04();

signals:
    void back();

private slots:
    void on_autoClean_Button_clicked();

    void on_manualClean_Button_clicked();

private:
    Ui::Page_04 *ui;
    //创建 写_预处理 对象
    writeProcess *writePro;
};

#endif // PAGE_04_H
