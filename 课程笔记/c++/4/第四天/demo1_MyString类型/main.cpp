
#include "head.h"


int main()
{
    MyString s1("hello");//�����вι��캯����ʵ������ռ�
    MyString s2(NULL);

    MyString s3 = s1;//�ַ����ĳ�ʼ�������ÿ������캯��

    MyString s4("123");
    //s4.operator=(s1);
    s4 = s1;//�ַ����ĸ�ֵ������=����������غ���

    //��װ<<���غ���
    //cout.operator<<(s1); �����������ʱ��Ҫ����Դ��д��cout��Ӧ������
    //cout ��Ӧostream��(�����ò���)�����Բ�����ʹ�ó�Ա����

    //operator<<(cout,s1);
    cout << "s1 = " << s1 << endl;//������Ϊ���غ���������void

    cout << "s3 = " << s3 << endl;
    cout << "s4 = " << s4 << endl;

    //s4.operator[](1)
    s4[1] = 'w';//hwllo
    cout << s4 << endl;

    //s4.operator==(s1)
    if(s4 == s1)
    {
        cout << "s4����s1" << endl;
    }
    else
    {
         cout << "s4������s1" << endl;
    }

    //s4.operator==("farsight")
    if(s4 == "farsight")
    //if("farsight" == s4) //���ֲ���������
    {
        cout << "��" << endl;
    }
    else
    {
        cout << "��" << endl;
    }

    return 0;
}
