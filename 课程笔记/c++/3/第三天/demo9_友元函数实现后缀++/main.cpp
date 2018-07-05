#include <iostream>

using namespace std;

class suffix_plus_plus
{
private:
    int a;
    int b;
    friend suffix_plus_plus& operator++(suffix_plus_plus& obj,int);
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
};

suffix_plus_plus& operator++(suffix_plus_plus& obj,int)
{
    obj.a ++;
    obj.b ++;
    return obj;
}

int main()
{
    suffix_plus_plus obj(1,2);

    //operator++(obj)
    //operator++(obj,int)
    obj++;
    obj.print();

    return 0;
}
