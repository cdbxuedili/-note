#include <iostream>

using namespace std;

class test
{
//private:
public:
    int a;
    int b;
    static int c;
public:
//    test(int mya,int myb,int myc)
//    {
//        a = mya;
//        b = myb;
//        c = myc;
//    }
    test(int mya,int myb)
    {
        a = mya;
        b = myb;
    }

    void print()
    {
        cout << "c = " << c << endl;
    }

    void add()
    {
        c = c + 1;
    }
};

int test::c = 100; //��̬��Ա�����ĳ�ʼ������

int main()
{
    //test t(1,2,3);//1���������˵����̬��Ա��������ʹ�ù��캯������ʼ��
    test t(1,2);

    //2����̬��Ա������γ�ʼ����
    //t.print();

    //3����̬��Ա�����ĵ��÷���(���ʿ���Ȩ�޵��ǹ��е�)
    cout << t.c << endl;
    cout << test::c << endl;

    //4����̬��Ա���������ڶ��󣬹����(���ʹ��ͬһ���࣬��ͬ�Ķ���֮�侲̬��Ա�����ǹ����)
    test t1(1,2);
    t1.add();

    test t2(3,4);
    t2.print();


    return 0;
}
