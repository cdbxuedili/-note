#include <iostream>

using namespace std;//�����ռ���߽������ƿռ�

int main()
{
    cout << "hello" << endl;//����ַ���,�����endl

    char a = 'b';
    cout << a << endl;//���a������ŵ��ַ�
    cout << (int)a << endl;//����ַ���asciiֵ

    int b = 10;
    cout << &b << endl;//�������������ַ
    cout << b << endl;//Ĭ�����ʮ��������
    cout << showbase << oct << b << endl;//����˽���,һ��������������
    cout << showbase << hex << b << endl;//���ʮ������

    int c;
    cout << "�������c��������:";
    cin >> c;//������c��������
    cout << showbase << dec << c << endl;//�Ļ�ʮ�������
    return 0;
}
