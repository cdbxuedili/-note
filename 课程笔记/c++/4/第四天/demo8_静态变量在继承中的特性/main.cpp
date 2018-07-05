#include <iostream>

using namespace std;

class parent
{
public:
    static int a;
};
int parent::a = 100;//静态变量的初始化方法

class child1:public parent
{
public:
    void add()
    {
        a = a + 1;
    }
};

class child2:public parent
{
public:
    void print()
    {
        cout << a << endl;
    }
};

int main()
{
    child1 c1;
    child2 c2;

    c1.add();
    c2.print();//打印结果为101，子类2并没有加过1，如果是直接继承那么结果应该是100，101的结果说明是共享
    return 0;
}
