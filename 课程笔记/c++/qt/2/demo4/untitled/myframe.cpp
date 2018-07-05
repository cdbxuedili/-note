#include "myframe.h"
#include<QDebug>
#include<QMouseEvent>
#include<QPainter>

myframe::myframe(QWidget *parent) :
    QFrame(parent)
{
}
void myframe::mousePressEvent(QMouseEvent * ev)
{
   // qDebug()<<ev->globalX()<<","<<ev->globalX();
    QPoint point(ev->x(),ev->y());
    points.push_back(point);
    update();
}


void myframe::mouseMoveEvent(QMouseEvent * ev)
{
   // qDebug()<<ev->globalX()<<","<<ev->globalX();
    QPoint point(ev->x(),ev->y());
    points.push_back(point);
    update();
}
void myframe::mouseReleaseEvent(QMouseEvent * ev)
{
   // qDebug()<<ev->globalX()<<","<<ev->globalX();
    QPoint point(ev->x(),ev->y());
    points.push_back(point);
    update();

}
void myframe::paintEvent(QPaintEvent *ev)
{/*
    QPainter p;
    p.begin(this);
    QPoint start(50,50);
    QPoint end(100,100);
    p.drawLine(start,end);
    p.end();*/
    QPainter pa;
    vector<QPoint>::iterator it;
    if(points.size()<=1)
        return;
    pa.begin(this);
    QPoint start = points[0];
    for(it = points.begin();it!=points.end();it++)
    {
        pa.drawLine(start,*it);
        start = *it;
    }
    pa.end();
}
