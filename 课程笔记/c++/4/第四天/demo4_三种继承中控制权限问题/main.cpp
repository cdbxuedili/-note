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

////���м̳У��̳к����������Ե�Ȩ�޺͸����ж�Ӧ���Ե�Ȩ����ͬ��
//class child:public parent
//{
//public:
//    void setvalue()
//    {
//        a = 1;
//        b = 2;
//       // c = 3;//������˽��������Ȼ���Ա��������̳У���������û��Ȩ��ʹ�ø����˽�����ԡ�
//    }
//};
//
//int main()
//{
//    cout << sizeof(child) << endl;//˽������Ҳ���̳���
//
//    child obj;
//    obj.a = 10;//��ȷ
//    //obj.b = 20;//����
//    //obj.c = 30;//����
//    return 0;
//}

//class child:protected parent
//{
////�����̣���Ҫд����
////protected:
////    int a;
////    int b;
////private:
////    int c;
//public:
//    void setvalue()
//    {
//        a = 1;//��ȷ
//        b = 2;//��ȷ
//        //c = 3;//����
//    }
//};
//
//int main()
//{
//    child obj;
//    //obj.a = 10;//����
//    //obj.b = 20;//����
//    //obj.c = 30;//����
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
        a = 1;//��ȷ��
        b = 2;//��ȷ
        //c = 3;//�����
    }
};

int main()
{
    child obj;
    //obj.a = 10;//����
    //obj.b = 20;//����
    //obj.c = 30;//����
    return 0;
}
