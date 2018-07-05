#include <iostream>

using namespace std;

//通过多态的方式来实现圆的面积和三角形的面积
class interface //抽象类
{
public:
    virtual void getarea() = 0;//纯虚函数
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
};

void test(interface *base)
{
    base->getarea();//会有多态产生
}

int main()
{
    circle c(3);
    triangle t(3,4);

    test(&c);
    test(&t);
    return 0;
}
