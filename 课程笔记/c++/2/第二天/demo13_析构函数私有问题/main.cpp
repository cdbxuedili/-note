#include <iostream>
#include <cstring>
using namespace std;

class test
{
private:
    char *p;
    int len;
//private:
public:
    test(const char *s)
    {
        len = strlen(s);
        p = new char [len + 1];
        strcpy(p,s);
    }

    void print()
    {
        cout << p << endl;
    }

    void mydestroy(test *pt)
    {
        delete pt;
    }
private:
    ~test()
    {
        delete [] p;
    }
};

int main()
{
    //test t("hello");//������캯��˽�л���ջ�����󲻿���ʹ��

    test *pt;
    pt = new test("hello");//������캯��˽�У���������Ҳ����ʹ��
    pt->print();
    pt->mydestroy(pt);
    //delete pt;//�ͷſռ䣬����һ���������ⲿ����������������������������˽�еģ����Ի����
    return 0;
}
