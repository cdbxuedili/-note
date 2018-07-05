#include <iostream>

using namespace std;

class test
{
private:
    int a;
    int b;

public:
    test()
    {
        a = 10;
        b = 20;
    }

    test(int mya,int myb)
    {
        a = mya;
        b = myb;
    }

    test(const test& obj)//��������һ�������ʼ��
    {
        a = obj.a;
        b = obj.b;
    }

    void print()
    {
        cout << a << endl;
        cout << b << endl;
    }
};

int main()
{

    test t1;//�����޲ι��캯��

    //test t2(1);//������Ϊ����û�ж���һ���������вι��캯��

    test t3(3,4);//��ȷ�����������������вι��캯��

    test t4(5,6);
    t4 = t3;//�ⲽ������������ĸ�ֵ,��仰��ִ��ʱ��������ÿ������캯�������õ���=�����������
    t4.print();//t4��������5��6�����3��4������������ʵ���˳�ʼ���������������ﲢ���ǳ�ʼ�������Ǹ�ֵ

    //test t5(10,20) = t3;//�����ˣ��������ÿ������캯����t5�ĺ��治����(10,20)��
    test t5 = t3;
    t5.print();
    return 0;
}
