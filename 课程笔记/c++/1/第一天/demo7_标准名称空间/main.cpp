#include <iostream>

//using namespace std;//std���Ǳ�׼���ƿռ������

int main()
{
//    std::cout << "hello" << std::endl;
    using std::cout;
    using std::endl;
    cout << "hello" << endl;
    cout << "world" << endl;

    using std::cin;
    return 0;
}
