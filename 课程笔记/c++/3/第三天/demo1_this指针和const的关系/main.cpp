#include <iostream>

using namespace std;

class test
{
private:
    int a;
    int b;
public:
    test(int a,int b)
    {
        this->a = a;
        this->b = b;
    }

    void print()
    {
        cout << this->a << endl;
        cout << this->b << endl;
    }

    //const void ModifyValue()
    //void const ModifyValue()
    void ModifyValue(int c) const //�������ָ�ʽ����ͬ�ģ���ôconst�����ڸ��const���ε���thisָ��Ŀռ�
    {
        //int x = 10;
        //x = 100; ����û�г���˵��const���������κ����ռ�Ϊֻ��

        //c = 200;//����û�д�const�������β���c��

        //��������Ĳ����л�������test *const this;
        //const test *const this;
        this->a = 30;
        this->b = 40;
    }

    ~test()
    {
        cout << "��������������" << endl;
    }
};

int main()
{
    test t(1,2);

    t.ModifyValue(100);
    return 0;
}
