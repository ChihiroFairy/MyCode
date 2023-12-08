#ifndef DEVICE02_H
#define DEVICE02_H

#include <QWidget>
#include "serialport.h"
#include "preproccess.h"

namespace Ui {
class device02;
}

class preproccess;
class device02 : public QWidget
{
    Q_OBJECT

public:
    explicit device02(QWidget *parent = nullptr);
    ~device02();

    //使用单例模式
    static device02 *get_ins();
    static device02 *dev02;

signals:
    void back();

private slots:
    void on_sendButton_clicked();
    void upDateDisplay(const QByteArray &data);

private:
    Ui::device02 *ui;
    preproccess *prePross;
};

#endif // DEVICE02_H
