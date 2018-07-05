#include <iostream>

using namespace std;

//假设有一个立方体(需要长、宽、高),获取立方体的面积和体积(面积变量和体积变量)
//先用面向过程的方法来实现
//class cube
//{
//public:
//    int a;
//    int b;
//    int c;
//    int s;
//    int v;
//};
//
//int getS(int a,int b,int c)
//{
//    return 2*(a * b + b * c + a * c);
//}
//
//int getV(int a,int b,int c)
//{
//    return a * b *c;
//}
//
//int main()
//{
//    cube obj;
//    cin >> obj.a;
//    cin >> obj.b;
//    cin >> obj.c;
//
//    obj.s = getS(obj.a,obj.b,obj.c);
//    obj.v = getV(obj.a,obj.b,obj.c);
//
//    cout << obj.s << endl;
//    cout << obj.v << endl;
//    return 0;
//}

class cube
{
private:
    int a;
    int b;
    int c;
    int s;
    int v;

public:
//    void initCube(int mya,int myb,int myc)
//    {
//        a = mya;
//        b = myb;
//        c = myc;
//    }
    cube(int mya,int myb,int myc)
    {
        a = mya;
        b = myb;
        c = myc;
    }

    int getS()
    {
        s = 2 *(a * b + a *c + b * c);
        return s;
    }

    int getV()
    {
        v = a * b * c;
        return v;
    }
};

int main()
{
 //   cube obj;
 //   obj.initCube(1,2,3);
    cube obj(1,2,3);
    cout << obj.getS() << endl;
    cout << obj.getV() << endl;
    return 0;
}
