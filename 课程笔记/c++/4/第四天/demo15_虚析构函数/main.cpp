#include <iostream>
#include <cstring>
using namespace std;

class A
{
private:
    char *p;
public:
    A()
    {
        p = new char [10];
        strcpy(p,"obja");
    }

    virtual ~A()
    {
        delete[] p;
        cout << "A����������" << endl;
    }
};

class B:public A
{
private:
    char *p;
public:
    B()
    {
        p = new char [10];
        strcpy(p,"objb");
    }

     ~B()
    {
        delete[] p;
        cout << "B����������" << endl;
    }
};

class C:public B
{
private:
    char *p;
public:
    C()
    {
        p = new char [10];
        strcpy(p,"objc");
    }
    ~C()
    {
        delete[] p;
        cout << "C����������" << endl;
    }
};

void deletefun(A *p)//�����õ��˸�ֵ������ԭ��
{
    delete p;//Ĭ��ֻ������A���������Ǳ���Ҫ����B��C����ʱ����������ǰ��virtual
            //ͨ����̬ʵ�������������ĵ���
}

int main()
{
    C *pc;

    pc = new C;

    //delete pc;
    deletefun(pc);

    return 0;
}
