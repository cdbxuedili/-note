#include <iostream>

using namespace std;

class A
{
private:
    int a;
    int b;
    int c;
};

class B
{
private:
    int a;
    int b;
    int c;
    static int d;
};

class C
{
private:
    int a;
    int b;
    int c;
    static int d;

public:
    void print()
    {

    }

    static void fun()
    {

    }
};

//��ͨ��Ա�����ڶ������Ż����ռ�
//��̬��Ա��������ͨ��������̬��Ա�������ඨ��ʱ���Ѿ������˿ռ�
//��ͨ��Ա�������ڴ��ջ���߶ѣ���̬��Ա�����ھ�̬�������еĳ�Ա�����ڴ������
int main()
{
    cout << sizeof(A) << endl;
    cout << sizeof(B) << endl;
    cout << sizeof(C) << endl;
    return 0;
}
