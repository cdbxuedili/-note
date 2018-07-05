#include <iostream>

using namespace std;

class Myplus
{
private:
    int a;
    int b;
    friend Myplus plusFun(Myplus& opd1,Myplus& opd2);
public:
    Myplus(int a=0,int b=0)
    {
        this->a = a;
        this->b = b;
    }

    void print()
    {
        cout << a << endl;
        cout << b << endl;
    }
};

Myplus plusFun(Myplus& opd1,Myplus& opd2)
{
    Myplus tmp;

    tmp.a = opd1.a + opd2.a;
    tmp.b = opd1.b + opd2.b;

    return tmp;
}

int main()
{
    Myplus opd1(1,2);
    Myplus opd2(3,4);

    Myplus ret;
    ret = plusFun(opd1,opd2);
    ret.print();
    return 0;
}
