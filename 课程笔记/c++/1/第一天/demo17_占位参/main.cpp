#include <iostream>

using namespace std;

int add(int a,int b,int) //�������������������ǰ׺�ͺ�׺++
{
    return a + b;
}

int myadd(int a,int b,int=0)//Ĭ�ϲκ�ռλ��ͬʱ����
{
    return a + b;
}

int main()
{
    int ret;
    ret = add(1,2,100);//����������û��ʹ�ã����Ǵ���ʱ������ʡ��
    cout << ret << endl;

    ret = myadd(3,4);
    cout << ret << endl;
    return 0;
}
