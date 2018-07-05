#include <QtGui/QApplication>
#include "mianwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Mianwindow w;
    w.show();
    
    return a.exec();
}
