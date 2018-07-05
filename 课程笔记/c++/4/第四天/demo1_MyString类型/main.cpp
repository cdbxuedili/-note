
#include "head.h"


int main()
{
    MyString s1("hello");//调用有参构造函数，实现申请空间
    MyString s2(NULL);

    MyString s3 = s1;//字符串的初始化，调用拷贝构造函数

    MyString s4("123");
    //s4.operator=(s1);
    s4 = s1;//字符串的赋值，调用=的运算符重载函数

    //封装<<重载函数
    //cout.operator<<(s1); 定义这个函数时需要将其源码写到cout对应的类中
    //cout 对应ostream类(我们用不了)，所以不可以使用成员函数

    //operator<<(cout,s1);
    cout << "s1 = " << s1 << endl;//出错，因为重载函数返回了void

    cout << "s3 = " << s3 << endl;
    cout << "s4 = " << s4 << endl;

    //s4.operator[](1)
    s4[1] = 'w';//hwllo
    cout << s4 << endl;

    //s4.operator==(s1)
    if(s4 == s1)
    {
        cout << "s4等于s1" << endl;
    }
    else
    {
         cout << "s4不等于s1" << endl;
    }

    //s4.operator==("farsight")
    if(s4 == "farsight")
    //if("farsight" == s4) //这种不可能重载
    {
        cout << "真" << endl;
    }
    else
    {
        cout << "假" << endl;
    }

    return 0;
}
