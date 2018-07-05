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

//    static void fun()
//    {
//        cout << this->a << endl;
//        cout << this->b << endl;
//    }
};

int main()
{
    test t(1,2);
    t.print();
    return 0;
}
