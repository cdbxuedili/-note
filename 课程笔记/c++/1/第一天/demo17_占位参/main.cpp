#include <iostream>

using namespace std;

int add(int a,int b,int) //运算符重载中用来区分前缀和后缀++
{
    return a + b;
}

int myadd(int a,int b,int=0)//默认参和占位参同时出现
{
    return a + b;
}

int main()
{
    int ret;
    ret = add(1,2,100);//第三个参数没有使用，但是传参时不可以省略
    cout << ret << endl;

    ret = myadd(3,4);
    cout << ret << endl;
    return 0;
}
