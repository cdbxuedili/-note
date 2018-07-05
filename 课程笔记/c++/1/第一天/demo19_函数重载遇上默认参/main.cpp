#include <iostream>

using namespace std;

int add(int a,int b,int c = 0)//这里使用了默认参
{
    return a + b + c;
}

int add(int a)
{
    return a;
}
//上面的两个add函数可以重载

int add(int a,int b) //当这个原型存在时，如果我们调用add(1,2),使用默认参可以，使用函数重载也可以，此时c++编译器分不清该调用谁
{
    return a + b;
}

int main()
{
    //以下两种情况都可以调用到具有add的默认参函数
    add(1,2);
    add(1,2,3);

    add(10);
    return 0;
}
