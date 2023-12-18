#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QMainWindow>
#include "page_01.h"
#include "page_02.h"
#include "page_03.h"
#include "page_04.h"
#include "page_05.h"
#include "page_06.h"
#include "pageopen.h"
#include "pageclose.h"

QT_BEGIN_NAMESPACE
namespace Ui { class HomePage; }
QT_END_NAMESPACE

class HomePage : public QMainWindow
{
    Q_OBJECT

public:
    HomePage(QWidget *parent = nullptr);
    ~HomePage();

private:
    Ui::HomePage *ui;

    PageOpen *pageOpen = NULL;    //开始下料页面
    PageClose *pageClose = NULL;    //关机页面
    Page_01 *page01 = NULL;    //精度页面
    Page_02 *page02 = NULL;    //产量页面
    Page_03 *page03 = NULL;    //气阀页面
    Page_04 *page04 = NULL;    //清灰页面
    Page_05 *page05 = NULL;    //模型页面
    Page_06 *page06 = NULL;    //设置页面
};
#endif // HOMEPAGE_H
