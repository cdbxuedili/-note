#include <iostream>

using namespace std;

struct test
{
    int a;
    char b;

    void fun()
    {
        cout << "hello" << endl;
    }
};

int main()
{
    //struct test x;
    test x;
    x.fun();
    return 0;
}
