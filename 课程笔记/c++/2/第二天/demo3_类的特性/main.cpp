#include <iostream>

using namespace std;

class test
{
public:
    int a;
//    void fun() //默认为内联函数
//    {
//        cout << "hello" << endl;
//    }
    void fun();
};
void test::fun() //好像是在类的外部定义，其实本质还是类的内容。 默认为非内联函数
{
    cout << "hello" << endl;
}

int main()
{
    test t;
    t.a = 100;//出错了，说a是私有的
    t.fun();//出错了，fun也是私有的
    return 0;
}
