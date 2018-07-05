#ifndef MYEVENT_H
#define MYEVENT_H

#include <QLineEdit>

class myevent : public QLineEdit
{
    Q_OBJECT
public:
    explicit myevent(QWidget *parent = 0);
protected:
    virtual void keyPressEvent(QKeyEvent *ev);
signals:
    
public slots:
    
};

#endif // MYEVENT_H
