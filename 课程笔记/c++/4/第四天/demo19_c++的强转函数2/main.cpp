#include <iostream>

using namespace std;

//const char *p���ε���pָ���(buf�ռ�)�ռ�Ϊֻ��
void test(const char *p) //Ϊ����ߺ����İ�ȫ��
{
    //*(p + 1) = 'w';//���޸�ֻ���ռ䣬���Իᱨ��

    char *s;

    s = const_cast<char *>(p);//ȥ��p�е�const����
    *(s + 1) = 'w';
}

int main()
{
    char buf[] = "hello";//�����ջ����ջ�����Ը�

    //char *buf = "hello";//��������������ڴ�й©��ִ��ʧ��
                        //�����.rodataֻ�����ݶ��У������Ը�
                        //���ָ��ָ���ԭ�пռ䱾��;߱�const���ԣ���ôconst_cast�Ͳ���������
    test(buf);
    cout << buf << endl;
    return 0;
}

