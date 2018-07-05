#ifndef __HEAD__H
#define __HEAD__H

#include<QObject>
#include<iostream>

using namespace std;

class SigObject:public QObject
{
Q_OBJECT

public:
	SigObject(QObject * parent  = 0);
	void sendVoid();
	void sendInt(int value);
signals:
	void sigVoid();
	void sigInt(int i);
};

class Slotobject:public QObject
{
Q_OBJECT
public:
	Slotobject(QObject* parent=0);
public slots:
	void onSigVoid();

	void onSigInt(int value);
};

#endif 
