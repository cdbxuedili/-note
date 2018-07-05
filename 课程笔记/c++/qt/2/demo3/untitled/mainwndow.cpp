#include "mainwndow.h"
#include "ui_mainwndow.h"

Mainwndow::Mainwndow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Mainwndow)
{
    ui->setupUi(this);
}

Mainwndow::~Mainwndow()
{
    delete ui;
}
