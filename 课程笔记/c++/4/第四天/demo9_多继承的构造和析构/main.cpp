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
        cout << "构造1" << endl;
    }
    ~parent1()
    {
        cout << "析构函数1" << endl;
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
        cout << "构造2" << endl;
    }

    ~parent2()
    {
        cout << "析构函数2" << endl;
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
        cout << "子类构造" << endl;
    }

    ~child()
    {
        cout << "子类的析构函数" << endl;
    }
};

//继承中，如果父类没有构造函数或者有无参构造函数时，在子类的构造函数后不需要加参数化列表
int main()
{
    child obj(1);
    return 0;
}
