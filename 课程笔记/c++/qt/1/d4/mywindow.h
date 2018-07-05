#ifndef __MYHEAD_H
#define __MYHEAD_H


#include<QApplication>
#include<QPushButton>
#include<QLineEdit>
#include<QLabel>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QWidget>

class Mywindow:public QWidget
{
private:
	QHBoxLayout * layout; //水平布局
	QPushButton * btn;//按钮
	QLineEdit * le;//文本框
	QLabel * lb;//标签
public:
	Mywindow(QWidget * parent=0);
	
};




#endif
