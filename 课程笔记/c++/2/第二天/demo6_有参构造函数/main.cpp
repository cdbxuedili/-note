#include <iostream>

using namespace std;

class test
{
private:
    int a;
    int b;

public:
    test(int mya,int myb) //��2�������Ĺ��캯��
    {
        a = mya;
        b = myb;
    }

    test(int mya) //��һ�������Ĺ��캯��
    {
        a = mya;
        b = 20;
    }

    void print()
    {
        cout << a << endl;
        cout << b << endl;
    }
};

int main()
{
    //test t1;//�����
    test t1(1,2);//��������ͬʱ�����캯�����Ρ�
    t1.print();

    test t2(10);
    t2.print();

    test t3 = 100;//1���������вι��캯�����η�ʽ
    t3.print();

    test t4 = (1,2,3,4,5);//�����ӡ5 20,���Ƕ��������
    t4.print();
    return 0;
}
