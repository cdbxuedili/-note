#include <iostream>

using namespace std;

class parent
{
public:
    void fun()
    {

    }

    virtual void fun(int a)
    {

    }

    void fun(int a,int b)
    {

    }

};

class child:public parent
{
public:
    void fun(int a)
    {

    }

    void fun(int a,int b)
    {

    }
};

int main()
{
    child c;
    c.fun();//本质是在调用继承过来的无参fun，但是父类和子类之间不允许重载
    return 0;
}
