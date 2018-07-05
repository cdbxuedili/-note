#include <iostream>

using namespace std;

int main()
{
    int a = 10;
//    const int& b;
//    b = a;

//    const int& b = 20;//对20取别名
//    const int& b = a + 1;
    const double& b = a;
    cout << b << endl;

    cout << &a << endl;
    cout << &b << endl;

    return 0;
}
