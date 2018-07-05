#include <iostream>

using namespace std;

int add(int a,int b)
{
    return a + b;
}

int add(const int& a,const int& b)
{
    return a + b;
}

int main()
{
    int ret;
    ret = add(1,2);//const int&类型和int类型不相同，但是调用add(1,2)时编译器同样分不清该调用谁
    cout << ret << endl;
    return 0;
}
