#include <iostream>

using namespace std;

int add(int a,int b,int c = 0)//����ʹ����Ĭ�ϲ�
{
    return a + b + c;
}

int add(int a)
{
    return a;
}
//���������add������������

int add(int a,int b) //�����ԭ�ʹ���ʱ��������ǵ���add(1,2),ʹ��Ĭ�ϲο��ԣ�ʹ�ú�������Ҳ���ԣ���ʱc++�������ֲ���õ���˭
{
    return a + b;
}

int main()
{
    //����������������Ե��õ�����add��Ĭ�ϲκ���
    add(1,2);
    add(1,2,3);

    add(10);
    return 0;
}
