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
        cout << "��������" <<endl;
    }
};

int main()
{
    test *p;

    p = new test(1,2);//����ѿռ䲢�ҳ�ʼ��(�����ͬʱ�����вι��캯��)
    p->print();

    delete p;
    return 0;
}
