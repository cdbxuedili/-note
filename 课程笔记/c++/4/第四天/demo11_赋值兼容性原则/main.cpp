#include <iostream>

using namespace std;

class parent
{
public:
    void print()
    {
        cout << "����" << endl;
    }
};

class child:public parent
{

};

int main()
{
    child c;

    c.print();//1������ֱ�ӵ�������ʹ��

    parent p1 = c;//2���������ֱ�Ӹ������ʼ��
    parent p2;
    p2 = c; //3������ֱ�Ӹ����ำֵ

    parent *pp;
    pp = &c;//����ָ�����ָ���������

    parent& name = c;//���������������ȡ����
    return 0;
}
