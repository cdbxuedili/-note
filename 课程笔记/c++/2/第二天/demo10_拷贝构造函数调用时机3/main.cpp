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
        cout << "��������������" <<endl;
    }
};

test fun()
{
    test t1(1,2);
    return t1;//��������ǰһ������ÿ������캯��
}

int main()
{
    test t = fun();
    t.print();
    return 0;
}
