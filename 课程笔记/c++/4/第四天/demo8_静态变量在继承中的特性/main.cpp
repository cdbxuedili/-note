#include <iostream>

using namespace std;

class parent
{
public:
    static int a;
};
int parent::a = 100;//��̬�����ĳ�ʼ������

class child1:public parent
{
public:
    void add()
    {
        a = a + 1;
    }
};

class child2:public parent
{
public:
    void print()
    {
        cout << a << endl;
    }
};

int main()
{
    child1 c1;
    child2 c2;

    c1.add();
    c2.print();//��ӡ���Ϊ101������2��û�мӹ�1�������ֱ�Ӽ̳���ô���Ӧ����100��101�Ľ��˵���ǹ���
    return 0;
}
