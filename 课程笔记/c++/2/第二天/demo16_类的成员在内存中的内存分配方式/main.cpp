#include <iostream>

using namespace std;

class A
{
private:
    int a;
    int b;
    int c;
};

class B
{
private:
    int a;
    int b;
    int c;
    static int d;
};

class C
{
private:
    int a;
    int b;
    int c;
    static int d;

public:
    void print()
    {

    }

    static void fun()
    {

    }
};

//普通成员变量在对象定义后才会分配空间
//静态成员变量、普通函数、静态成员函数在类定义时就已经分配了空间
//普通成员变量在内存的栈或者堆，静态成员变量在静态区、所有的成员函数在代码段中
int main()
{
    cout << sizeof(A) << endl;
    cout << sizeof(B) << endl;
    cout << sizeof(C) << endl;
    return 0;
}
