#include <iostream>

using namespace std;

class prefix_plus_plus
{
private:
    int a;
    int b;
public:
    prefix_plus_plus(int a,int b)
    {
        this->a = a;
        this->b = b;
    }

    void print()
    {
        cout << a << endl;
        cout << b << endl;
    }

    prefix_plus_plus& operator++()
    {
        ++this->a;
        ++this->b;
        return *this;
    }
};


int main()
{
    prefix_plus_plus obj(1,2);

    //obj.operator++()
    ++obj;
    obj.print();
    return 0;
}
