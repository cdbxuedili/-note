#include <iostream>

using namespace std;

class parent
{
protected:
    int a;
public:
    parent()
    {
        a = 10;
    }
    virtual void print()
    {
        cout << "����:" << a << endl;
    }
};

class child:public parent
{
protected:
    int b;
public:
    child()
    {
        b = 20;
    }

    void print()
    {
        cout << "����:" << b << endl;
    }
};

void fun1(parent *base)
{
    base->print();
}

//void fun2(parent& name)
//{
//    name.print();
//}

int main()
{
    child c;//�������
    parent p;//�������

//    parent *base;//����ָ��
//
//    base = &p;//����ָ��ָ�������
//    base->print();//��ӡ����
//
//    base = &c;//����ָ��ָ���������
//    base->print();//��ӡ����
//
//    parent& name1 = p;//�������ø��������ȡ����
//    name1.print();
//
//    parent& name2 = c;//�������ø��������ȡ����
//    name2.print();

    fun1(&p);
    fun1(&c);

//    fun2(p);
//    fun2(c);
    return 0;
}
