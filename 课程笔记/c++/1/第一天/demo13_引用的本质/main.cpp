#include <iostream>

using namespace std;

struct test //�ڴ���룬����4�ֽڶ���
{
    char name[15];//ʵ��ʹ��16�ֽ�
    char& b;//ʵ��ʹ��4�ֽ�
    int a;//4�ֽ�
    char *p;//ֻҪ��һ��ָ���������32λ�����¶�ռ��4�ֽ�

};

int main()
{
    cout << sizeof(struct test) << endl;
    return 0;
}
