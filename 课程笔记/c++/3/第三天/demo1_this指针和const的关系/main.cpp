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

    void print()
    {
        cout << this->a << endl;
        cout << this->b << endl;
    }

    //const void ModifyValue()
    //void const ModifyValue()
    void ModifyValue(int c) const //以上三种格式是相同的，那么const到底在干嘛？const修饰的是this指向的空间
    {
        //int x = 10;
        //x = 100; 编译没有出错，说明const并不是修饰函数空间为只读

        //c = 200;//编译没有错，const不是修饰参数c的

        //这个函数的参数中还隐藏了test *const this;
        //const test *const this;
        this->a = 30;
        this->b = 40;
    }

    ~test()
    {
        cout << "析构函数被调用" << endl;
    }
};

int main()
{
    test t(1,2);

    t.ModifyValue(100);
    return 0;
}
