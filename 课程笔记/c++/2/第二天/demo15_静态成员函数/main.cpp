#include <iostream>

using namespace std;

class test
{
public:
    static void print()
    {
        cout << "hello" << endl;
    }
};

int main()
{
    test t;
    //t.print();
    test::print();//���ڲ�ͬ�Ķ�����˵����̬��Ա����Ҳ�ǹ���ġ�
    return 0;
}
