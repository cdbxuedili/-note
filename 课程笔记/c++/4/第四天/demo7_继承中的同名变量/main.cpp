#include <iostream>

using namespace std;

class parent
{
public:
    int a;
    int b;

    void printP()
    {
        cout << b << endl;
    }
};

class child:public parent
{
public:
 //   int a;
 //   int b;
    int b;
    int c;

//    void printP()
//    {
//        cout << b << endl;
//    }

    void printC()
    {
        cout << b << endl;
    }
};

int main()
{
    child obj;

    parent p;
    p.b = 200;//父类自己在初始化b的值
    p.printP();
    obj.printC();//子类在使用b，出现了随机值，并没有使用父类的值(使用的就是自己的b)
    obj.printP();

    cout << sizeof(child) << endl;//结果为16，说明同名变量继承后没有被覆盖
    return 0;
}
