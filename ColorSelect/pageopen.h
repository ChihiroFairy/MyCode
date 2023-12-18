#ifndef PAGEOPEN_H
#define PAGEOPEN_H

#include <QDialog>
#include "writeprocess.h"

namespace Ui {
class PageOpen;
}

class PageOpen : public QDialog
{
    Q_OBJECT

public:
    explicit PageOpen(QWidget *parent = nullptr);
    ~PageOpen();

signals:
   void back();

private slots:
   void on_startStopButton_clicked();

private:
    Ui::PageOpen *ui;
    //创建 写_预处理 对象
    writeProcess *writePro;
    //用于判断当前是否在下料中
    bool started;
};

#endif // PAGEOPEN_H
