#include <iostream>
#include <cstring>
using namespace std;

class test
{
private:
    int len;
    char *p;

public:
//private:
    test(const char *s)
    {
        len = strlen(s);
        p = new char[len + 1];
        strcpy(p,s);
    }
public:
    test(const test& obj)
    {
        len = obj.len;
        p = new char [len + 1];
        strcpy(p,obj.p);
    }

    void print()
    {
        cout << p << endl;
    }

    ~test()
    {
        delete[] p;
        p = NULL;
        len = 0;
        cout << "析构函数" << endl;
    }
};


int main()
{
    test t1("hello");//有参构造函数

    test t2 = t1;//如果我们自己没有实现拷贝构造函数，调用默认拷贝构造函数(实现浅拷贝)
                 //析构时p指向的空间会被释放两次，容易出现内存泄漏。为了避免最好使用深拷贝
    t2.print();
    return 0;
}

