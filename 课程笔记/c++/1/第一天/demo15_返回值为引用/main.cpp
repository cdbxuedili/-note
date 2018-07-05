#include <iostream>

using namespace std;

//int fun() //返回一个基本类型
//{
//    int a = 10;
//    return a;
//}

int& fun()
{
    int a = 10;
    return a;//只要返回，a空间会被释放
}

int main()
{
//    int ret;

//    ret = fun();
//    const int& ret = fun();//使用const引用来接收返回值，这种情况不建议使用

//    ret = fun();//确实fun函数返回了引用，但是对返回的引用做了备份。此时ret不是a的别名
//    cout << ret << endl;
//    cout << ret << endl;

    int& ret = fun();//ret是a的别名，接收的就是a的本身
    cout << ret << endl;
    cout << ret << endl;//出现乱码，因为a被释放了。

    return 0;
}
