#include <iostream>

using namespace std;

class test
{
private:
    int a;
    int b;
public:
    test()
    {
        a = 10;
        b = 20;
    }

    void print()
    {
        cout << a << endl;
        cout << b << endl;
    }
};

int main()
{
    test t;
    t.print();
    return 0;
}
