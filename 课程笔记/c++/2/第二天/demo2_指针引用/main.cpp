#include <iostream>
#include <cstdlib>

using namespace std;

struct stu
{
    char *name;
    int id;
};

//void initStu(stu **p)
//{
//    stu *tmp;
//
//    tmp = (stu *)malloc(sizeof(stu));
//    tmp->name = "lxs";
//    tmp->id = 1000;
//
//    *p = tmp;//tmp���Ǹ������p��ʼ��
//}
//
//int main()
//{
//    stu *s;
//    initStu(&s);
//    cout << s->name << endl;
//    cout << s->id <<endl;
//    return 0;
//}

void initStu(stu *& p)//p��s�ı���
{
    p = (stu *)malloc(sizeof(stu));
    p->name = "lxs";
    p->id = 1000;
}

int main()
{
    stu *s;

    initStu(s);
    cout << s->name << endl;
    cout << s->id << endl;
    return 0;
}
