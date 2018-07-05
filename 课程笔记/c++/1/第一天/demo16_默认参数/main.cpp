#include <iostream>

using namespace std;

int add(int a,int b = 50,int c=100)
{
    return a + b + c;
}

int main()
{
    int ret;
    ret = add(1,2,3);
    cout << ret << endl;
    //ret = add(1,2);
    ret = add(1);
    cout << ret << endl;
    return 0;
}
