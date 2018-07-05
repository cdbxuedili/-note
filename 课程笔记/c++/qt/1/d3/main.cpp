#include<QApplication>
#include<QPushButton>
#include<QLineEdit>
#include<QLabel>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QWidget>

int main(int argc, char **argv)
{
	QApplication app(argc,argv);

	QWidget  window;//空白窗口空间

//	QVBoxLayout * layout = new QVBoxLayout();// 垂直布局 

	QHBoxLayout * layout1 = new QHBoxLayout();//水平布局
	//QHBoxLayout * layout2 = new QHBoxLayout();//水平布局
	//窗口控件
	QPushButton * btn1 = new QPushButton("regiter",&window);//窗口内部按钮
	QLineEdit * le1 = new QLineEdit(&window);//窗口内部文本输入
	QLabel * lb1 = new QLabel("name",&window);//窗口内部标签

/*	
	QPushButton * btn2 = new QPushButton("login",&window);//窗口内部按钮
	QLineEdit * le2 = new QLineEdit(&window);//窗口内部文本输入
	QLabel * lb2 = new QLabel("psword",&window);//窗口内部标签
	btn.show();
	le.show();
	label.show();//将label设为可见
*/
	//将控件加入布局
	layout1 ->addWidget(lb1);
	layout1 ->addWidget(le1);
	layout1 ->addWidget(btn1); 
/*
	layout2 ->addWidget(lb2);
	layout2 ->addWidget(le2);
	layout2 ->addWidget(btn2); 
*/
//	layout ->addWidget(layout1);
//	layout ->addWidget(layout2);

	//将窗口布局设为水平布局
	window.setLayout(layout1);
	//window.setLayout(layout2);
	//设置窗口可见
	window.show();

	app.exec();
	return 0;
}


