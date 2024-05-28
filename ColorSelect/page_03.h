#ifndef PAGE_03_H
#define PAGE_03_H

#include <QWidget>
#include "writeprocess.h"
#include "readprocess.h"

namespace Ui {
class Page_03;
}

class Page_03 : public QWidget
{
    Q_OBJECT

public:
    explicit Page_03(QWidget *parent = nullptr);
    ~Page_03();

signals:
    void back();

private slots:
    void on_singleChe_Button_clicked();

    void on_multiChe_Button_clicked();

    void on_saveButton_clicked();
    void checkSlot();

    //void updateDisplay(const QByteArray &data);

private:
    Ui::Page_03 *ui;
    //创建 写_预处理 对象
    writeProcess *writePro;
    readProcess *readPro;

    QTimer* timer;  // 在这里声明 QTimer 指针
    int dec;
    bool inProgress;  // 用于跟踪函数是否正在执行的标志
};

#endif // PAGE_03_H
