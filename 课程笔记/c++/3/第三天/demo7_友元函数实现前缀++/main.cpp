#include <iostream>

using namespace std;

class prefix_plus_plus
{
private:
    int a;
    int b;
    friend prefix_plus_plus& operator++(prefix_plus_plus& obj);
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
};

prefix_plus_plus& operator++(prefix_plus_plus& obj)
{
    ++obj.a;
    ++obj.b;
    return obj;
}

int main()
{
    prefix_plus_plus obj(1,2);
    //operator++(obj);
    ++ obj;
    obj.print();
    return 0;
}
