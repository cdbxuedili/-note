#include <iostream>

using namespace std;

int main()
{
    double a = 1.1;
    int b;
 //   b = (int)a;
 //   b = int (a);
    b = static_cast<int>(a);
    cout << b << endl;

    int *p;
    char *q;
    //q = (char *)p;
    //q = static_cast<char *>(p);//���ת���������ܲ���ָ�룬ֻ�ܲ�����ͨ����(c�����п��Խ�����ʽǿת�Ķ�����ʹ���������)

    q = reinterpret_cast<char *>(p);

    int c = 1000;
    int *pb;

    //pb = (int *)c;
    //pb = static_cast<int *>(c);//������
    pb = reinterpret_cast<int *>(c);//���Ե�
    return 0;
}
