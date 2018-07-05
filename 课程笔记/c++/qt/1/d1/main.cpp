#include<QApplication>
#include<QLabel>



int main(int argc, char **argv)
{
	QApplication app(argc,argv);

	QLabel label("hello world");

	label.show();//将label设为可见

	app.exec();
	return 0;
}


