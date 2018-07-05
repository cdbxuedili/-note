#include <iostream>

//using namespace std;//std就是标准名称空间的名字

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
