#include <iostream>

using namespace std;//命名空间或者叫做名称空间

int main()
{
    cout << "hello" << endl;//输出字符串,必须加endl

    char a = 'b';
    cout << a << endl;//输出a变量存放的字符
    cout << (int)a << endl;//输出字符的ascii值

    int b = 10;
    cout << &b << endl;//用来输出变量地址
    cout << b << endl;//默认输出十进制整数
    cout << showbase << oct << b << endl;//输出八进制,一次设置终身受用
    cout << showbase << hex << b << endl;//输出十六进制

    int c;
    cout << "请给变量c输入内容:";
    cin >> c;//给变量c输入内容
    cout << showbase << dec << c << endl;//改回十进制输出
    return 0;
}
