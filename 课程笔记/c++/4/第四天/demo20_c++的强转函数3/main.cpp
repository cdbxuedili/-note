#include <iostream>

using namespace std;

//ͨ����̬�ķ�ʽ��ʵ��Բ������������ε����
class interface //������
{
public:
    virtual void getarea() = 0;//���麯��
};

class circle:public interface
{
protected:
    int r;
public:
    circle(int r)
    {
        this->r = r;
    }

    void getarea()
    {
        cout << 3.14 * r * r << endl;
    }

    void printC()
    {
        cout << "Բ��" << endl;
    }
};

class triangle:public interface
{
protected:
    int a;
    int b;

public:
    triangle(int a,int b)
    {
        this->a = a;
        this->b = b;
    }

    void getarea()
    {
        cout << a * b / 2 << endl;
    }

    void printT()
    {
        cout << "������" << endl;
    }
};

void test(interface *base)
{
    base->getarea();//���ж�̬����

    //Ϊ���ڶ�̬��ȥִ�з��麯��
    circle *pc = dynamic_cast<circle *>(base);//����ǿת

    if(pc != NULL)
    {
        pc->printC();
    }

    triangle *pt = dynamic_cast<triangle *>(base);
    if(pt != NULL)
    {
        pt->printT();
    }
}

int main()
{
    circle c(3);
    triangle t(3,4);

    test(&c);
    //test(&t);
    return 0;
}
