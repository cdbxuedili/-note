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
        cout << "test�Ĺ��캯��" << endl;
    }

    ~test()
    {
        cout << "test����������" << endl;
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
        cout << "���๹�캯��" << endl;
    }

    ~parent()
    {
        cout << "�������������" << endl;
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
        cout << "���๹�캯��" << endl;
    }
    ~child()
    {
        cout << "�������������" << endl;
    }

    void print()
    {
        cout << a << endl;
        cout << b << endl;
        //cout << c << endl; ������ϲ��Ǽ̳�
    }
};


int main()
{
    child obj(1);
    obj.print();
    obj.t.printT();
    return 0;
}
