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

void fun(test t)
{
    t.print();
}

int main()
{
    test t1(1,2);

    fun(t1);
    return 0;
}
