#include <QtGui/QApplication>
#include "mainwndow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Mainwndow w;
    w.show();
    
    return a.exec();
}
