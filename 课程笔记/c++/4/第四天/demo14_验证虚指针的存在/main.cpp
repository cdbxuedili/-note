#include <iostream>

using namespace std;

class A //c++�п���Ĭ��Ϊ1����������Ϊ����ʱ��СΪ0
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
    cout << sizeof(C) << endl;//Ϊ4˵������һ��ָ������Ĵ�С
    return 0;
}
