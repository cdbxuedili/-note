#include <iostream>

using namespace std;

void fun(int a)
{
    cout << "一个参数的fun:a = " << a << endl;
}

void fun(int a,int b)
{
    cout << "二个参数的fun:a = " << a << ",b = " << b<< endl;
}

int main()
{
    fun(10);
    fun(1,2);
    return 0;
}
