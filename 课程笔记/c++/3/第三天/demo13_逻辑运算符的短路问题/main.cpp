#include <iostream>

using namespace std;

struct test
{
private:
    int a;
public:
    test(int a=0)
    {
        this->a = a;
    }

    test& operator+(test& opd2)
    {
        static test tmp;
        tmp.a = this->a + opd2.a;
        return tmp;
    }

    bool operator&&(test& obj)
    {
        if(this->a == 0)
            return false;
        else
        {
            if(obj.a == 0)
                return false;
            else
                return true;
        }
    }
};

int main()
{
    test t1(0);
    test t2(1);

    //t1.operator(t1 + t2�Ľ��)
    if(t1 && t1 + t2) //��Ȼt1Ϊ�٣����ǻ���ִ����t1 + t2�����������������������޷�����(�ƻ����߼�������Ķ�·����)
    {
        cout << "����Ϊ��" << endl;
    }
    else
    {
        cout << "����Ϊ��" << endl;
    }
    return 0;
}
