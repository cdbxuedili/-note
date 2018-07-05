#include <iostream>

using namespace std;

class A //c++中空类默认为1，当空类作为基类时大小为0
{

};

class B
{
public:
    void print()
    {

    }
};

class C
{
public:
    virtual void print()
    {

    }
};

int main()
{
    cout << sizeof(A) << endl;
    cout << sizeof(B) << endl;
    cout << sizeof(C) << endl;//为4说明多了一个指针变量的大小
    return 0;
}
