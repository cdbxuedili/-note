#ifndef MAINWNDOW_H
#define MAINWNDOW_H

#include <QWidget>

namespace Ui {
class Mainwndow;
}

class Mainwndow : public QWidget
{
    Q_OBJECT
    
public:
    explicit Mainwndow(QWidget *parent = 0);
    ~Mainwndow();
    
private:
    Ui::Mainwndow *ui;
};

#endif // MAINWNDOW_H
