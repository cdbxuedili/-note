#include <iostream>
#include <cstdio>

using namespace std;

int main()
{
    int a = 10;
    int b = 20;

    a > b ? a : b = 100;//��ȷ�ģ���Ϊb�Ǳ���
    //a > b ? 1 : 2 = 100;//����ģ���Ϊ2�ǳ���
    printf("a = %d,b = %d\n",a,b);
    return 0;
}
