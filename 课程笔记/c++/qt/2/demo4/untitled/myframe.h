#ifndef MYFRAME_H
#define MYFRAME_H

#include <QFrame>
#include <vector>
#include<QPoint>

using namespace std;

class myframe : public QFrame
{
    Q_OBJECT

private:
    vector<QPoint> points;
public:
    explicit myframe(QWidget *parent = 0);
protected:
    virtual void mousePressEvent(QMouseEvent * ev);
    virtual void mouseMoveEvent(QMouseEvent * ev);
    virtual void mouseReleaseEvent(QMouseEvent * ev);
    virtual void paintEvent(QPaintEvent *ev);
signals:
    
public slots:
    
};

#endif // MYFRAME_H
