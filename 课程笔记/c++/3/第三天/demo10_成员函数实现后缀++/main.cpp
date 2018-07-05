#include <iostream>

using namespace std;

class suffix_plus_plus
{
private:
    int a;
    int b;
public:
    suffix_plus_plus(int a,int b)
    {
        this->a = a;
        this->b = b;
    }

    void print()
    {
        cout << a << endl;
        cout << b << endl;
    }

    suffix_plus_plus& operator++(int)
    {
        this->a ++;
        this->b ++;
        return *this;
    }
};

int main()
{
    suffix_plus_plus obj(1,2);

    //opd.operator++(int)
    obj++;
    obj.print();
    return 0;
}
