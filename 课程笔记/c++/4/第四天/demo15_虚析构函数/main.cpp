#include <iostream>
#include <cstring>
using namespace std;

class A
{
private:
    char *p;
public:
    A()
    {
        p = new char [10];
        strcpy(p,"obja");
    }

    virtual ~A()
    {
        delete[] p;
        cout << "A的析构函数" << endl;
    }
};

class B:public A
{
private:
    char *p;
public:
    B()
    {
        p = new char [10];
        strcpy(p,"objb");
    }

     ~B()
    {
        delete[] p;
        cout << "B的析构函数" << endl;
    }
};

class C:public B
{
private:
    char *p;
public:
    C()
    {
        p = new char [10];
        strcpy(p,"objc");
    }
    ~C()
    {
        delete[] p;
        cout << "C的析构函数" << endl;
    }
};

void deletefun(A *p)//传参用到了赋值兼容性原则
{
    delete p;//默认只会析构A，但是我们必须要析构B和C，此时在析构函数前加virtual
            //通过多态实现了析构函数的调用
}

int main()
{
    C *pc;

    pc = new C;

    //delete pc;
    deletefun(pc);

    return 0;
}
