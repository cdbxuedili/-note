#include <iostream>

using namespace std;

class parent
{
public:
    int a;
    int b;

    void printP()
    {
        cout << b << endl;
    }
};

class child:public parent
{
public:
 //   int a;
 //   int b;
    int b;
    int c;

//    void printP()
//    {
//        cout << b << endl;
//    }

    void printC()
    {
        cout << b << endl;
    }
};

int main()
{
    child obj;

    parent p;
    p.b = 200;//�����Լ��ڳ�ʼ��b��ֵ
    p.printP();
    obj.printC();//������ʹ��b�����������ֵ����û��ʹ�ø����ֵ(ʹ�õľ����Լ���b)
    obj.printP();

    cout << sizeof(child) << endl;//���Ϊ16��˵��ͬ�������̳к�û�б�����
    return 0;
}
