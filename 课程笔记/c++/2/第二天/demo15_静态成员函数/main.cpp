#include <iostream>

using namespace std;

class test
{
public:
    static void print()
    {
        cout << "hello" << endl;
    }
};

int main()
{
    test t;
    //t.print();
    test::print();//对于不同的对象来说，静态成员函数也是共享的。
    return 0;
}
