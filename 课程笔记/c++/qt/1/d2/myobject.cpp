#include"myobject.h"

SigObject::SigObject(QObject * parent)
	:QObject(parent)
{

}

void SigObject::sendVoid()
{
	emit sigVoid();
}

void SigObject::sendInt(int value)
{

	emit sigInt(value);
}

Slotobject::Slotobject(QObject * parent)
	 :QObject(parent)
{

}

void Slotobject::onSigVoid()
{
	cout <<"hello world";
}


void Slotobject::onSigInt(int value)
{
	cout << "hello linux"<<value;

}


