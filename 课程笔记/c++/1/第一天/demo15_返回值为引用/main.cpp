#include <iostream>

using namespace std;

//int fun() //����һ����������
//{
//    int a = 10;
//    return a;
//}

int& fun()
{
    int a = 10;
    return a;//ֻҪ���أ�a�ռ�ᱻ�ͷ�
}

int main()
{
//    int ret;

//    ret = fun();
//    const int& ret = fun();//ʹ��const���������շ���ֵ���������������ʹ��

//    ret = fun();//ȷʵfun�������������ã����ǶԷ��ص��������˱��ݡ���ʱret����a�ı���
//    cout << ret << endl;
//    cout << ret << endl;

    int& ret = fun();//ret��a�ı��������յľ���a�ı���
    cout << ret << endl;
    cout << ret << endl;//�������룬��Ϊa���ͷ��ˡ�

    return 0;
}
