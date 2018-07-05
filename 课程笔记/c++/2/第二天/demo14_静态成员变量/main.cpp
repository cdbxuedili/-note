#include <iostream>

using namespace std;

class test
{
//private:
public:
    int a;
    int b;
    static int c;
public:
//    test(int mya,int myb,int myc)
//    {
//        a = mya;
//        b = myb;
//        c = myc;
//    }
    test(int mya,int myb)
    {
        a = mya;
        b = myb;
    }

    void print()
    {
        cout << "c = " << c << endl;
    }

    void add()
    {
        c = c + 1;
    }
};

int test::c = 100; //静态成员变量的初始化方法

int main()
{
    //test t(1,2,3);//1、编译出错，说明静态成员变量不能使用构造函数来初始化
    test t(1,2);

    //2、静态成员变量如何初始化？
    //t.print();

    //3、静态成员变量的调用方法(访问控制权限得是公有的)
    cout << t.c << endl;
    cout << test::c << endl;

    //4、静态成员变量不属于对象，共享的(如果使用同一个类，不同的对象之间静态成员变量是共享的)
    test t1(1,2);
    t1.add();

    test t2(3,4);
    t2.print();


    return 0;
}
