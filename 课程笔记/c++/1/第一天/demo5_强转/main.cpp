#include <iostream>

using namespace std;

int main()
{
    int a;
    double b;

    //������ͨ���ͣ����·�ʽ������
    //b = (double)a;
    //b = double (a);

    b = static_cast <double>(a);//c++��չ��ǿת��ʽ
    return 0;
}
