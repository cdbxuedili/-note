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
    ret = add(1,2);//const int&���ͺ�int���Ͳ���ͬ�����ǵ���add(1,2)ʱ������ͬ���ֲ���õ���˭
    cout << ret << endl;
    return 0;
}
