#include <iostream>

using namespace std;

//const char *p修饰的是p指向的(buf空间)空间为只读
void test(const char *p) //为了提高函数的安全性
{
    //*(p + 1) = 'w';//在修改只读空间，所以会报错

    char *s;

    s = const_cast<char *>(p);//去除p中的const属性
    *(s + 1) = 'w';
}

int main()
{
    char buf[] = "hello";//存放在栈区，栈区可以改

    //char *buf = "hello";//这种情况出现了内存泄漏，执行失败
                        //存放在.rodata只读数据段中，不可以改
                        //如果指针指向的原有空间本身就具备const属性，那么const_cast就不起作用了
    test(buf);
    cout << buf << endl;
    return 0;
}

