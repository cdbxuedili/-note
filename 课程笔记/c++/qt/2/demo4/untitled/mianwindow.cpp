#include "mianwindow.h"
#include "ui_mianwindow.h"

Mianwindow::Mianwindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Mianwindow)
{
    ui->setupUi(this);
}

Mianwindow::~Mianwindow()
{
    delete ui;
}
