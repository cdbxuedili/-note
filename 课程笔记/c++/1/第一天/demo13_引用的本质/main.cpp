#include <iostream>

using namespace std;

struct test //内存对齐，按照4字节对齐
{
    char name[15];//实际使用16字节
    char& b;//实际使用4字节
    int a;//4字节
    char *p;//只要是一个指针变量，在32位环境下都占用4字节

};

int main()
{
    cout << sizeof(struct test) << endl;
    return 0;
}
