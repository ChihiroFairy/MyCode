#ifndef PAGECLOSE_H
#define PAGECLOSE_H

#include <QDialog>

namespace Ui {
class PageClose;
}

class PageClose : public QDialog
{
    Q_OBJECT

public:
    explicit PageClose(QWidget *parent = nullptr);
    ~PageClose();

signals:
    //返回主页面
   void back();

private:
    Ui::PageClose *ui;
};

#endif // PAGECLOSE_H
