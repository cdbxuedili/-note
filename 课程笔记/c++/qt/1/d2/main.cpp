#include<QApplication>
#include"myobject.h"

int main(int argc,char ** argv)
{
	QApplication app(argc,argv);

	SigObject sigObj;
	Slotobject slotobj;

	QObject::connect(&sigObj,SIGNAL(sigVoid()),&slotobj,SLOT(onSigVoid()));

	sigObj.sendVoid();
//	sigObj.sendInt(5);

	return app.exec();
} 
