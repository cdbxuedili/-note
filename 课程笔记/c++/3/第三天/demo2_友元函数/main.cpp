#include <iostream>

using namespace std;

class test
{
private:
    int a;
    friend void fun(test *p);//һ����������仰����ôȫ�ֺ���fun�ͱ������Ԫ����

public:
    test(int a)
    {
        this->a = a;
    }

    void print()
    {
        cout << a << endl;
    }
};

void fun(test *p)
{
    p->a = 200;//Ĭ���ǲ��ܲ������ڲ���˽�г�Ա�ģ�����ᱨ��
               //ƫƫ���������ã���Ԫ�����ó����ˡ�
}

int main()
{
    test t(10);
    fun(&t);
    return 0;
}
