#include <iostream>

using namespace std;

int add(int a,int b)
{
    return a + b;
}

int add(int a,int b,int c)
{
    return a + b + c;
}

//int (*p)(int,int); p是函数指针变量名
//typedef int (*p)(int,int);p是函数指针类型名
//typedef int (p)(int,int);p是函数类型名
int main()
{
    typedef int (FunType)(int,int);
    FunType *pAdd;

    pAdd = add;
    cout << pAdd(1,2) << endl;
    //cout << pAdd(1,2,3) << endl;//报错，因为函数指针不能间接实现函数重载

    return 0;
}
