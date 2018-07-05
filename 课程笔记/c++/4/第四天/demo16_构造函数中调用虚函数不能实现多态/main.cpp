#include <iostream>

using namespace std;

class base
{
private:
    int a;
public:
    base(int a = 0)
    {
        this->a = a;
        print();
    }

    virtual void print()
    {
        cout << "base" << endl;
    }
};

class child:public base
{
private:
    int b;
public:
    child(int b):base(10)
    {
        this->b = b;
        print();
    }

    virtual void print()
    {
        cout << "child" << endl;
    }
};

int main()
{
    child c(20);

    base *p = &c;//�Ѿ�ָ���������������ж�̬��ֻ����������print����
                 //ʵ��������ȵ����˸����print������������������print����
                 //����Ĺ��캯���е����麯��ʱ����ʵ�ֶ�̬
    return 0;
}
