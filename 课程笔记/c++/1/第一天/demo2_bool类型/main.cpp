#include <iostream>
//#include <stdio.h>
#include <cstdio>
using namespace std;

int main()
{
    bool a = 10;
    //bool a = true;
    a++;//正确的，支持自增
    //a --;不支持自减
    printf("%d\n",a);
    return 0;
}
