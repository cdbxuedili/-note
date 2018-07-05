#include <iostream>
#include <cstring>
using namespace std;

class test
{
private:
    int len;
    char *p;

public:
//private:
    test(const char *s)
    {
        len = strlen(s);
        p = new char[len + 1];
        strcpy(p,s);
    }
public:
    test(const test& obj)
    {
        len = obj.len;
        p = new char [len + 1];
        strcpy(p,obj.p);
    }

    void print()
    {
        cout << p << endl;
    }

    ~test()
    {
        delete[] p;
        p = NULL;
        len = 0;
        cout << "��������" << endl;
    }
};


int main()
{
    test t1("hello");//�вι��캯��

    test t2 = t1;//��������Լ�û��ʵ�ֿ������캯��������Ĭ�Ͽ������캯��(ʵ��ǳ����)
                 //����ʱpָ��Ŀռ�ᱻ�ͷ����Σ����׳����ڴ�й©��Ϊ�˱������ʹ�����
    t2.print();
    return 0;
}

