#include "myevent.h"
#include<QDebug>
#include<QKeyEvent>>

myevent::myevent(QWidget *parent) :
    QLineEdit(parent)
{
}

void myevent::keyPressEvent(QKeyEvent *ev)
{
    QLineEdit::keyPressEvent(ev);

    qDebug()<<"root"<<(ev->text());
}
