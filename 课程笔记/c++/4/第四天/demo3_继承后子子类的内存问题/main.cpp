#include <iostream>

using namespace std;

class parent
{
public:
    int a;
    int b;

    void printP()
    {
        cout << "parent" << endl;
        cout << a << endl;
        cout << b << endl;
    }
};

class child:public parent
{
public:
    int c;

    void printC()
    {
        cout << a << endl;
        cout << b << endl;
        cout << c << endl;
    }
};

int main()
{
    cout << sizeof(child) << endl;

    child obj;
    obj.a = 10;//ͨ���������ʹ�ôӸ���̳й���������
    obj.b = 20;
    obj.c = 30;

    obj.printC();
    obj.printP();//ʹ���˼̳к�ķ�����(�Ժ������˱��ݣ����õ��������Լ��Ĵ�ӡ����)
    obj.parent::printP();//ʹ�õ��Ǹ��౾��Ĵ�ӡ����
    return 0;
}
