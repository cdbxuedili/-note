#include <iostream>
#include <cstdio>

using namespace std;

void fun()
{
    static int a = 10,b = 20,c = 0;

    c = a + b + c;
    printf("%d\n",c);
}

int main()
{
    const int a = 10;
    int *p = (int *)&a;

    *p = 100;
    printf("a = %d\n",a);

    register int b;
    printf("%p\n",&b);

    fun();
    fun();
    return 0;
}
