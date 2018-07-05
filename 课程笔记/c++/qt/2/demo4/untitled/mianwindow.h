#ifndef MIANWINDOW_H
#define MIANWINDOW_H

#include <QWidget>

namespace Ui {
class Mianwindow;
}

class Mianwindow : public QWidget
{
    Q_OBJECT
    
public:
    explicit Mianwindow(QWidget *parent = 0);
    ~Mianwindow();
    
private:
    Ui::Mianwindow *ui;
};

#endif // MIANWINDOW_H
