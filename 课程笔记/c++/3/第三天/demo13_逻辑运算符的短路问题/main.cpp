#include <iostream>

using namespace std;

struct test
{
private:
    int a;
public:
    test(int a=0)
    {
        this->a = a;
    }

    test& operator+(test& opd2)
    {
        static test tmp;
        tmp.a = this->a + opd2.a;
        return tmp;
    }

    bool operator&&(test& obj)
    {
        if(this->a == 0)
            return false;
        else
        {
            if(obj.a == 0)
                return false;
            else
                return true;
        }
    }
};

int main()
{
    test t1(0);
    test t2(1);

    //t1.operator(t1 + t2的结果)
    if(t1 && t1 + t2) //虽然t1为假，但是还是执行了t1 + t2，这种情况在运算符重载中无法避免(破坏了逻辑运算符的短路规则)
    {
        cout << "条件为真" << endl;
    }
    else
    {
        cout << "条件为假" << endl;
    }
    return 0;
}
