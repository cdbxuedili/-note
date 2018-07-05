#include <iostream>

using namespace std;

class A
{
private:
    int a;
public:
    A(int a)
    {
        this->a = a;
    }

    void printA()
    {
        cout << a << endl;
    }
};

class B
{
private:
    int b;

public:
    A a1;
    A a2;

public:
    B(int b):a1(1),a2(2)//û�г�ʼ��a1��a2����
    {
        this->b = b;
    }

    void printB()
    {
        cout << this->b << endl;
    }
};

int main()
{
    B obj(10);
    obj.printB();
    //obj.printA();
    obj.a1.printA();
    obj.a2.printA();
    return 0;
}
