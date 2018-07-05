#include <iostream>

using namespace std;

class test
{
private:
    int *p;

public:
    test()
    {
        p = new int(10);
    }

    void print()
    {
        cout << *p << endl;
    }

    ~test()
    {
        delete p;
        p = NULL;
    }
};

int main()
{
    test t;
    t.print();
    return 0;
}
