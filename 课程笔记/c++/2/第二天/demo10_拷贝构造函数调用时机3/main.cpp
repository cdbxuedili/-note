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

    test(const test& obj)
    {
        a = obj.a;
        b = obj.b;
    }

    ~test()
    {
        cout << "析构函数被调用" <<endl;
    }
};

test fun()
{
    test t1(1,2);
    return t1;//正常返回前一定会调用拷贝构造函数
}

int main()
{
    test t = fun();
    t.print();
    return 0;
}
