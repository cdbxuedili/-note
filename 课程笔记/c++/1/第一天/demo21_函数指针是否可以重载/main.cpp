#include <iostream>

using namespace std;

int add(int a,int b)
{
    return a + b;
}

int add(int a,int b,int c)
{
    return a + b + c;
}

//int (*p)(int,int); p�Ǻ���ָ�������
//typedef int (*p)(int,int);p�Ǻ���ָ��������
//typedef int (p)(int,int);p�Ǻ���������
int main()
{
    typedef int (FunType)(int,int);
    FunType *pAdd;

    pAdd = add;
    cout << pAdd(1,2) << endl;
    //cout << pAdd(1,2,3) << endl;//������Ϊ����ָ�벻�ܼ��ʵ�ֺ�������

    return 0;
}
