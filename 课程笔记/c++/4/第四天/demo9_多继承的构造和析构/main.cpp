#include <iostream>

using namespace std;

class parent1
{
private:
    int a;

public:
//    parent1()
//    {
//        a = 10;
//    }
    parent1(int a)
    {
        this->a = a;
        cout << "����1" << endl;
    }
    ~parent1()
    {
        cout << "��������1" << endl;
    }
};

class parent2
{
protected:
    int b;
public:
//    parent2()
//    {
//        b = 20;
//    }
    parent2(int b)
    {
        this->b = b;
        cout << "����2" << endl;
    }

    ~parent2()
    {
        cout << "��������2" << endl;
    }
};

class child:public parent2,public parent1
{
private:
    int c;

public:
    child(int c):parent1(3),parent2(4)
    {
        this->c = c;
        cout << "���๹��" << endl;
    }

    ~child()
    {
        cout << "�������������" << endl;
    }
};

//�̳��У��������û�й��캯���������޲ι��캯��ʱ��������Ĺ��캯������Ҫ�Ӳ������б�
int main()
{
    child obj(1);
    return 0;
}
