#include <iostream>

using namespace std;

class parent
{
public:
    int a;
    int b;

    void printP()
    {
        cout << "parent" << endl;
        cout << a << endl;
        cout << b << endl;
    }
};

class child:public parent
{
public:
    int c;

    void printC()
    {
        cout << a << endl;
        cout << b << endl;
        cout << c << endl;
    }
};

int main()
{
    cout << sizeof(child) << endl;

    child obj;
    obj.a = 10;//通过子类可以使用从父类继承过来的属性
    obj.b = 20;
    obj.c = 30;

    obj.printC();
    obj.printP();//使用了继承后的方法。(对函数做了备份，调用的是子类自己的打印函数)
    obj.parent::printP();//使用的是父类本身的打印函数
    return 0;
}
