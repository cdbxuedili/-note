#include <iostream>

using namespace std;

class plus_reload
{
private:
    int a;
    int b;
    friend plus_reload operator+(const plus_reload& a1,const plus_reload& a2);
    //friend plus_reload& operator+(const plus_reload& a1,const plus_reload& a2);
public:
    plus_reload(int a=0,int b=0)
    {
        this->a = a;
        this->b = b;
    }

    void print()
    {
        cout << this->a << endl;
        cout << this->b << endl;
    }
};

plus_reload operator+(const plus_reload& a1,const plus_reload& a2)//����ʱʹ���˱��ʽ��֧������+
{
    plus_reload tmp;

    tmp.a = a1.a + a2.a;
    tmp.b = a1.b + a2.b;

    return tmp;//����ǰ��tmp���˱���(tmp�����ͷ�Ҳû��Ӱ��)
}

//plus_reload& operator+(const plus_reload& a1,const plus_reload& a2) //��֧������+
//{
//    plus_reload tmp;
//
//    tmp.a = a1.a + a2.a;
//    tmp.b = a1.b + a2.b;
//
//    return tmp;//���ص���tmp����һ���������ִ����tmp�ᱻ�ͷ�
//}

int main()
{
    plus_reload a1(1,2);
    plus_reload a2(3,4);
    plus_reload a3(5,6);
    plus_reload a4(7,8);

    plus_reload ret;
    //ret = operator+(a1,a2);
    //ret = a1 + a2;//Ŀ�ľ���Ҫʹ��+�����������
    //ret.print();

    ret = a1 + a2 + a3 + a4;
    ret.print();
    return 0;
}
