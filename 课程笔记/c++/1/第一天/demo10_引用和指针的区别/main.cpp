#include <iostream>

using namespace std;

int main()
{
    int a = 10;
    int& b = a;

    a = 100;
    cout << a << endl;
    cout << b << endl;

    cout << &a << endl;
    cout << &b << endl;
    return 0;
}
