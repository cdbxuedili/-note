#include <iostream>

using namespace std;

class test
{
private:
    int a;
    friend void fun(test *p);//一旦声明了这句话，那么全局函数fun就变成了友元函数

public:
    test(int a)
    {
        this->a = a;
    }

    void print()
    {
        cout << a << endl;
    }
};

void fun(test *p)
{
    p->a = 200;//默认是不能操作类内部的私有成员的，编译会报错。
               //偏偏就想这样用，友元函数该出场了。
}

int main()
{
    test t(10);
    fun(&t);
    return 0;
}
