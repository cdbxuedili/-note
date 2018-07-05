#include <iostream>

using namespace std;

class parent
{
public:
    void print()
    {
        cout << "父类" << endl;
    }
};

class child:public parent
{

};

int main()
{
    child c;

    c.print();//1、子类直接当做父类使用

    parent p1 = c;//2、子类可以直接给父类初始化
    parent p2;
    p2 = c; //3、子类直接给父类赋值

    parent *pp;
    pp = &c;//父类指针可以指向子类对象

    parent& name = c;//父类对象给子类对象取别名
    return 0;
}
