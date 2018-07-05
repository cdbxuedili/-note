#include <iostream>

using namespace std;

int main()
{
    int a;
    double b;

    //对于普通类型，以下方式都可以
    //b = (double)a;
    //b = double (a);

    b = static_cast <double>(a);//c++扩展的强转方式
    return 0;
}
