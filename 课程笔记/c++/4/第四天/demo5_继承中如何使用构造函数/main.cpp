#include <iostream>

using namespace std;

class base
{
protected:
    int a;
public:
    base(int a)
    {
        this->a = a;
        cout << "����Ĺ��캯��" << endl;
    }

    ~base()
    {
        cout << "�������������" << endl;
    }
};

class child:public base
{
private:
    int b;

public:
    child(int b):base(20)
    {
        this->b = b;
        cout << "����Ĺ��캯��" << endl;
    }

    child(int b,int m):base(m)
    {
        this->b = b;
    }

    void printC()
    {
        cout << a << endl;
        cout << b << endl;
    }

    ~child()
    {
        cout << "������������" << endl;
    }
};

int main()
{
    child c1(10);
    c1.printC();

 //   child c2(1,2);
 //   c2.printC();
    return 0;
}
