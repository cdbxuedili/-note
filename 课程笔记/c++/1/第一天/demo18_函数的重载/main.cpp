#include <iostream>

using namespace std;

void fun(int a)
{
    cout << "һ��������fun:a = " << a << endl;
}

void fun(int a,int b)
{
    cout << "����������fun:a = " << a << ",b = " << b<< endl;
}

int main()
{
    fun(10);
    fun(1,2);
    return 0;
}
