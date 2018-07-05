#include "mywindow.h"


Mywindow::Mywindow(QWidget * parent)
	:QWidget(parent)
{
	layout = new QHBoxLayout(this);
	btn = new QPushButton("login",this);
	le = new QLineEdit(this);
	lb = new QLabel("name",this);

	layout->addWidget(lb);
	layout->addWidget(le);
	layout->addWidget(btn);

	this ->setLayout(layout);

} 
