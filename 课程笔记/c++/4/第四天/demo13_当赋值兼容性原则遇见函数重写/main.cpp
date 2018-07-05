#include <iostream>

using namespace std;

class parent
{
protected:
    int a;
public:
    parent()
    {
        a = 10;
    }
    virtual void print()
    {
        cout << "父类:" << a << endl;
    }
};

class child:public parent
{
protected:
    int b;
public:
    child()
    {
        b = 20;
    }

    void print()
    {
        cout << "子类:" << b << endl;
    }
};

void fun1(parent *base)
{
    base->print();
}

//void fun2(parent& name)
//{
//    name.print();
//}

int main()
{
    child c;//子类对象
    parent p;//父类对象

//    parent *base;//父类指针
//
//    base = &p;//父类指针指向父类对象
//    base->print();//打印父类
//
//    base = &c;//父类指针指向子类对象
//    base->print();//打印父类
//
//    parent& name1 = p;//父类引用给父类对象取别名
//    name1.print();
//
//    parent& name2 = c;//父类引用给子类对象取别名
//    name2.print();

    fun1(&p);
    fun1(&c);

//    fun2(p);
//    fun2(c);
    return 0;
}
