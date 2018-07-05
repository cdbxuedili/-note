#include <iostream>

using namespace std;

class test
{
private:
    int a;
    int b;

public:
    test(int mya,int myb) //有2个参数的构造函数
    {
        a = mya;
        b = myb;
    }

    test(int mya) //有一个参数的构造函数
    {
        a = mya;
        b = 20;
    }

    void print()
    {
        cout << a << endl;
        cout << b << endl;
    }
};

int main()
{
    //test t1;//错误的
    test t1(1,2);//定义对象的同时给构造函数传参。
    t1.print();

    test t2(10);
    t2.print();

    test t3 = 100;//1个参数的有参构造函数传参方式
    t3.print();

    test t4 = (1,2,3,4,5);//结果打印5 20,这是逗号运算符
    t4.print();
    return 0;
}
