#include <iostream>
#include "head.h"

using namespace std;

int main()
{
    MyArray arr1(3);

    int i;

    for(i = 0;i < arr1.getlen();i ++)
    {
        //arr1.setvalue(i,i);
        //arr1.operation[](int index)
        arr1[i] = i;
    }

    for(i = 0;i < arr1.getlen();i ++)
    {
        //cout << arr1.getvalue(i) << endl;
        cout << arr1[i] << endl;
    }

    MyArray arr2 = arr1;//初始化，调用拷贝构造函数
    for(i = 0;i < arr2.getlen();i ++)
    {
        cout << arr2[i] << endl;
    }

    MyArray arr3(5);
    //arr3.operator=(arr1)
    arr3 = arr1;//赋值,调用=重载函数
    for(i = 0;i < arr3.getlen();i ++)
    {
        cout << arr3[i] << endl;
    }

    return 0;
}
