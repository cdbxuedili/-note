#include <iostream>

using namespace std;

class test
{
public:
    int a;
//    void fun() //Ĭ��Ϊ��������
//    {
//        cout << "hello" << endl;
//    }
    void fun();
};
void test::fun() //������������ⲿ���壬��ʵ���ʻ���������ݡ� Ĭ��Ϊ����������
{
    cout << "hello" << endl;
}

int main()
{
    test t;
    t.a = 100;//�����ˣ�˵a��˽�е�
    t.fun();//�����ˣ�funҲ��˽�е�
    return 0;
}
