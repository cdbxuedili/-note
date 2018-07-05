#include <iostream>

using namespace std;


class grandparent
{
protected:
    int a;

public:
    //grandparent(int a)
    grandparent()
    {
        a = 100;
    }
};

class parent1:virtual public grandparent
{
protected:
    int b1;
public:
    //parent1(int b1):grandparent(100),���ֵ��÷�ʽ���ʼ����Σ����ǹ��캯��ֻ��Ҫ��ʼ��һ��
    parent1(int b1)
    {
        this->b1 = b1;
    }
};

class parent2:virtual public grandparent
{
protected:
    int b2;
public:
    //parent2(int b2):grandparent(200)
    parent2(int b2)
    {
        this->b2 = b2;
    }
};

class child:public parent1,public parent2  //��̳�
{
protected:
    int c;
public:
    child(int c):parent1(1),parent2(2)
    {
        this->c = c;
    }

    void print()
    {
        cout << a << endl;//ֱ�ӵ���a����ֶ����ԣ���ν�������virtual�ؼ���(��̳�)
        cout << b1 << endl;
        cout << b2 << endl;
    }
};


int main()
{
    child obj(3);
    obj.print();
    return 0;
}
