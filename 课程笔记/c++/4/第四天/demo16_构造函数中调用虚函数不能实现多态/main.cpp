#include <iostream>

using namespace std;

class base
{
private:
    int a;
public:
    base(int a = 0)
    {
        this->a = a;
        print();
    }

    virtual void print()
    {
        cout << "base" << endl;
    }
};

class child:public base
{
private:
    int b;
public:
    child(int b):base(10)
    {
        this->b = b;
        print();
    }

    virtual void print()
    {
        cout << "child" << endl;
    }
};

int main()
{
    child c(20);

    base *p = &c;//已经指向了子类对象，如果有多态则只会调用子类的print函数
                 //实际情况是先调用了父类的print函数，最后调用了子类print函数
                 //父类的构造函数中调用虚函数时不能实现多态
    return 0;
}
