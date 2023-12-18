#include "PageClose_sub.h"
#include "ui_PageClose_sub.h"

PageClose_sub::PageClose_sub(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PageClose_sub)
{
    ui->setupUi(this);
}

PageClose_sub::~PageClose_sub()
{
    delete ui;
}
