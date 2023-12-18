#ifndef PAGE01_SUB_H
#define PAGE01_SUB_H

#include <QDialog>

namespace Ui {
class PageOpen_sub;
}

class PageClose_sub : public QDialog
{
    Q_OBJECT

public:
    explicit PageClose_sub(QWidget *parent = nullptr);
    ~PageClose_sub();
signals:
    //返回主界面
    void back();

private:
    Ui::PageClose_sub *ui;
};

#endif // PAGE01_SUB_H
