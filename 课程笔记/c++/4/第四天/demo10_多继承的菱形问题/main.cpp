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
    //parent1(int b1):grandparent(100),这种调用方式会初始化多次，但是构造函数只需要初始化一次
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

class child:public parent1,public parent2  //多继承
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
        cout << a << endl;//直接调用a会出现二义性，如何解决？添加virtual关键字(虚继承)
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
