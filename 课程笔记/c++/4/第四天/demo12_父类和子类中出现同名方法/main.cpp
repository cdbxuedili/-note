#include <iostream>

using namespace std;

class parent
{
public:
    void fun()
    {

    }

    virtual void fun(int a)
    {

    }

    void fun(int a,int b)
    {

    }

};

class child:public parent
{
public:
    void fun(int a)
    {

    }

    void fun(int a,int b)
    {

    }
};

int main()
{
    child c;
    c.fun();//�������ڵ��ü̳й������޲�fun�����Ǹ��������֮�䲻��������
    return 0;
}
