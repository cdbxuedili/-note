#include <iostream>
#include <cstring>
using namespace std;

class test
{
private:
    char *p;
    int len;
//private:
public:
    test(const char *s)
    {
        len = strlen(s);
        p = new char [len + 1];
        strcpy(p,s);
    }

    void print()
    {
        cout << p << endl;
    }

    void mydestroy(test *pt)
    {
        delete pt;
    }
private:
    ~test()
    {
        delete [] p;
    }
};

int main()
{
    //test t("hello");//如果构造函数私有化，栈区对象不可以使用

    test *pt;
    pt = new test("hello");//如果构造函数私有，堆区对象也不能使用
    pt->print();
    pt->mydestroy(pt);
    //delete pt;//释放空间，所以一定会从类的外部调用析构函数，但是析构函数是私有的，所以会出错。
    return 0;
}
