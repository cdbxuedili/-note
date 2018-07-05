#include <iostream>

using namespace std;

class test
{
private:
    int c;
public:
    test(int c)
    {
        this->c = c;
        cout << "test的构造函数" << endl;
    }

    ~test()
    {
        cout << "test的析构函数" << endl;
    }

    void printT()
    {
        cout << c << endl;
    }
};

class parent
{
protected:
    int a;
public:
    parent(int a)
    {
        this->a = a;
        cout << "父类构造函数" << endl;
    }

    ~parent()
    {
        cout << "父类的析构函数" << endl;
    }
};

class child:public parent
{
private:
    int b;
public:
    test t;
public:
    child(int b):parent(10),t(20)
    {
        this->b = b;
        cout << "子类构造函数" << endl;
    }
    ~child()
    {
        cout << "子类的析构函数" << endl;
    }

    void print()
    {
        cout << a << endl;
        cout << b << endl;
        //cout << c << endl; 这是组合不是继承
    }
};


int main()
{
    child obj(1);
    obj.print();
    obj.t.printT();
    return 0;
}
