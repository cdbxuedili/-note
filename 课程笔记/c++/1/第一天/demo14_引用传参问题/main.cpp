#include <iostream>

using namespace std;

//void swap(int x,int y)//ֵ����
//{
//    int tmp;
//
//    tmp = x;
//    x = y;
//    y = tmp;
//    cout << "x = " << x << "," << "y = " << y << endl;
//}

//void swap(int *p,int *q)
//{
//    int tmp;
//    tmp = *p;
//    *p = *q;
//    *q = tmp;
//
//    cout << "*p = " << *p << "," << "*q = " << *q << endl;
//}

void swap(int& a,int& b)
{
    int tmp;

    tmp = a;
    a = b;
    b = tmp;
    cout << "swap:a = " << a << "," << "b = " << b << endl;
}

int main()
{
    int a = 10;
    int b = 20;
 //   swap(a,b);//ֵ����

  //  swap(&a,&b);//��ַ����

    swap(a,b);//���ô���
    cout << "main:a = " << a << "," << "b = " << b << endl;
    return 0;
}
