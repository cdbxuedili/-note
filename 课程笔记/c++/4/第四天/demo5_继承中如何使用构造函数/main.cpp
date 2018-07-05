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
        cout << "父类的构造函数" << endl;
    }

    ~base()
    {
        cout << "父类的析构函数" << endl;
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
        cout << "子类的构造函数" << endl;
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
        cout << "子类析构函数" << endl;
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
