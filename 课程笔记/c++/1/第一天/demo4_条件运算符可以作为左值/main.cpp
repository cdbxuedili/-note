#include <iostream>
#include <cstdio>

using namespace std;

int main()
{
    int a = 10;
    int b = 20;

    a > b ? a : b = 100;//正确的，因为b是变量
    //a > b ? 1 : 2 = 100;//错误的，因为2是常量
    printf("a = %d,b = %d\n",a,b);
    return 0;
}
