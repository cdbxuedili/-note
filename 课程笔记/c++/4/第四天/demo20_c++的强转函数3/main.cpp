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

    void printC()
    {
        cout << "圆形" << endl;
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
        cout << "三角形" << endl;
    }
};

void test(interface *base)
{
    base->getarea();//会有多态产生

    //为了在多态中去执行非虚函数
    circle *pc = dynamic_cast<circle *>(base);//向下强转

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
