#include <iostream>

using namespace std;

class plus_reload
{
private:
    int a;
    int b;
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

//    plus_reload operator+(plus_reload& obj) //֧������+
//    {
//        plus_reload tmp;
//        tmp.a = this->a + obj.a;
//        tmp.b = this->b + obj.b;
//        return tmp;
//    }

//     plus_reload& operator+(plus_reload& obj) //��֧������+
//     {
//        plus_reload tmp;
//        tmp.a = this->a + obj.a;
//        tmp.b = this->b + obj.b;
//        return tmp;
//     }

//    plus_reload operator+(plus_reload& obj) //֧������+
//    {
//        this->a = this->a + obj.a;
//        this->b = this->b + obj.b;
//        return *this;
//    }

    plus_reload& operator+(plus_reload& obj) //֧������+
    {
        this->a = this->a + obj.a;
        this->b = this->b + obj.b;
        return *this;//���thisָ��a1��a1������������ⲿ���壬����a1�����ͷ�
    }

};

int main()
{
    plus_reload a1(1,2);
    plus_reload a2(3,4);
    plus_reload a3(5,6);
    plus_reload a4(7,8);

    plus_reload ret;
    //a1.operator+(a2);
    //ret = a1 + a2;
    //ret.print();

    ret = a1 + a2 + a3 + a4;
    ret.print();
    return 0;
}
