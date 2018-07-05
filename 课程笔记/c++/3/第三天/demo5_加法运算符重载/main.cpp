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

plus_reload operator+(const plus_reload& a1,const plus_reload& a2)//传参时使用了表达式，支持连续+
{
    plus_reload tmp;

    tmp.a = a1.a + a2.a;
    tmp.b = a1.b + a2.b;

    return tmp;//返回前对tmp做了备份(tmp就算释放也没有影响)
}

//plus_reload& operator+(const plus_reload& a1,const plus_reload& a2) //不支持连续+
//{
//    plus_reload tmp;
//
//    tmp.a = a1.a + a2.a;
//    tmp.b = a1.b + a2.b;
//
//    return tmp;//返回的是tmp本身，一旦这个函数执行完tmp会被释放
//}

int main()
{
    plus_reload a1(1,2);
    plus_reload a2(3,4);
    plus_reload a3(5,6);
    plus_reload a4(7,8);

    plus_reload ret;
    //ret = operator+(a1,a2);
    //ret = a1 + a2;//目的就是要使用+的运算符重载
    //ret.print();

    ret = a1 + a2 + a3 + a4;
    ret.print();
    return 0;
}
