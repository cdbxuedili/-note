#include <iostream>

using namespace std;


//int main()
//{
//    //申请空间来存放一个整数
//    int *p;
//
//    p = new int;//只申请空间，不初始化
//    p = new int(100);//申请空间同时初始化
//    //*p = 100;
//    cout << *p << endl;
//    delete p;
//    return 0;
//}


int main()
{
    //申请5个int类型的空间
    int *p;

    //p = new int [5]{6,7,8,9,10};//申请空间的同时初始化
    p = new int [5];//申请多个数据空间
                    //p = new [5] int这种是错误的
    for(int i = 0;i < 5;i ++)
    {
        p[i] = i;
    }

    for(int i=0;i < 5;i ++)
    {
        cout << p[i] << endl;
    }
    delete[] p; //delete p[]这种是错误的

    return 0;
}
