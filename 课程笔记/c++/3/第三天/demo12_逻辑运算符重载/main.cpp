#include <iostream>

using namespace std;

struct test
{
private:
    int a;
public:
    test(int a)
    {
        this->a = a;
    }

    bool operator&&(test& t2)
    {
        if(this->a == 0)
            return false;
        else
        {
            if(t2.a == 0)
                return false;
            else
                return true;
        }
    }
};

int main()
{
    test t1(0);
    test t2(20);

    //��Ա������: t1.operator&&(t2)
    if(t1 && t2)
    {
        cout << "��������" << endl;
    }
    else
    {
        cout << "����ʧ��" << endl;
    }
    return 0;
}
