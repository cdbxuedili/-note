#include <iostream>

using namespace std;

int main()
{
    double a = 1.1;
    int b;
 //   b = (int)a;
 //   b = int (a);
    b = static_cast<int>(a);
    cout << b << endl;

    int *p;
    char *q;
    //q = (char *)p;
    //q = static_cast<char *>(p);//这个转换函数不能操作指针，只能操作普通类型(c语言中可以进行隐式强转的都可以使用这个函数)

    q = reinterpret_cast<char *>(p);

    int c = 1000;
    int *pb;

    //pb = (int *)c;
    //pb = static_cast<int *>(c);//不可以
    pb = reinterpret_cast<int *>(c);//可以的
    return 0;
}
