#include <iostream>

using namespace std;

class test
{
private:
    int a;
    int b;
public:
    test(int a,int b)
    {
        this->a = a;
        this->b = b;
    }

    int operator()(int x,int y)
    {
        return x * y;
    }
};

int main()
{
    test t(1,2);//调用两个参数的构造函数

    //t.operator()(3,4);
    cout <<t(3,4) << endl;
    return 0;
}
