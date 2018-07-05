#include "mywindow.h"

int main(int argc,char **argv)
{
	QApplication app(argc,argv);

	Mywindow mv;

	mv.show();
	return app.exec();
}
