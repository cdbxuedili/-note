#include <iostream>

using namespace std;

class test
{
private:
    int a;
    int b;

public:
    test()
    {
        a = 10;
        b = 20;
    }

    test(int mya,int myb)
    {
        a = mya;
        b = myb;
    }

    test(const test& obj)//用来给另一个对象初始化
    {
        a = obj.a;
        b = obj.b;
    }

    void print()
    {
        cout << a << endl;
        cout << b << endl;
    }
};

int main()
{

    test t1;//调用无参构造函数

    //test t2(1);//出错，因为我们没有定义一个参数的有参构造函数

    test t3(3,4);//正确，调用两个参数的有参构造函数

    test t4(5,6);
    t4 = t3;//这步操作叫做对象的赋值,这句话在执行时并不会调用拷贝构造函数，调用的是=的运算符重载
    t4.print();//t4的属性由5，6变成了3，4看起来好像是实现了初始化工作，但是这里并不是初始化，而是赋值

    //test t5(10,20) = t3;//报错了，如果想调用拷贝构造函数，t5的后面不能有(10,20)。
    test t5 = t3;
    t5.print();
    return 0;
}
