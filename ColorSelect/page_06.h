#ifndef PAGE_06_H
#define PAGE_06_H

#include <QWidget>
#include "portsettings.h"
#include "page06_1.h"
#include "page06_2.h"
#include "page06_3.h"

namespace Ui {
class Page_06;
}

class Page_06 : public QWidget
{
    Q_OBJECT

public:
    explicit Page_06(QWidget *parent = nullptr);
    ~Page_06();

signals:
    //返回主页面
    void back();

private:
    Ui::Page_06 *ui;

    PortSettings *portSets;
    Page06_1 *page06_01 = NULL; //相机设置页面
    Page06_2 *page06_02 = NULL; //恒流源板调节页面
    Page06_3 *page06_03 = NULL; //图像获取页面
};

#endif // PAGE_06_H
