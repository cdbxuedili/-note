#include <iostream>

using namespace std;

class test
{
private:
    int a;
    int b;
public:
    test(int mya,int myb)
    {
        a = mya;
        b = myb;
    }

    void print()
    {
        cout << a << endl;
        cout << b << endl;
    }
    ~test()
    {
        cout << "析构函数" <<endl;
    }
};

int main()
{
    test *p;

    p = new test(1,2);//申请堆空间并且初始化(申请的同时调用有参构造函数)
    p->print();

    delete p;
    return 0;
}
