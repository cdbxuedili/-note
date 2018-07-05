#include <iostream>

using namespace std;

class parent
{
public:
    int a;
protected:
    int b;
private:
    int c;
};

////公有继承，继承后子类中属性的权限和父类中对应属性的权限相同的
//class child:public parent
//{
//public:
//    void setvalue()
//    {
//        a = 1;
//        b = 2;
//       // c = 3;//父类中私有属性虽然可以被子类所继承，但是子类没有权限使用父类的私有属性。
//    }
//};
//
//int main()
//{
//    cout << sizeof(child) << endl;//私有属性也被继承了
//
//    child obj;
//    obj.a = 10;//正确
//    //obj.b = 20;//错误
//    //obj.c = 30;//错误
//    return 0;
//}

//class child:protected parent
//{
////理解过程，不要写出来
////protected:
////    int a;
////    int b;
////private:
////    int c;
//public:
//    void setvalue()
//    {
//        a = 1;//正确
//        b = 2;//正确
//        //c = 3;//错误
//    }
//};
//
//int main()
//{
//    child obj;
//    //obj.a = 10;//错误
//    //obj.b = 20;//错误
//    //obj.c = 30;//错误
//    return 0;
//}

class child:private parent
{
//private:
//    int a;
//    int b;
//    int c;
public:
    void setvalue()
    {
        a = 1;//正确的
        b = 2;//正确
        //c = 3;//错误的
    }
};

int main()
{
    child obj;
    //obj.a = 10;//错误
    //obj.b = 20;//错误
    //obj.c = 30;//错误
    return 0;
}
