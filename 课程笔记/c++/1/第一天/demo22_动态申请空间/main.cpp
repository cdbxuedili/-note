#include <iostream>

using namespace std;


//int main()
//{
//    //����ռ������һ������
//    int *p;
//
//    p = new int;//ֻ����ռ䣬����ʼ��
//    p = new int(100);//����ռ�ͬʱ��ʼ��
//    //*p = 100;
//    cout << *p << endl;
//    delete p;
//    return 0;
//}


int main()
{
    //����5��int���͵Ŀռ�
    int *p;

    //p = new int [5]{6,7,8,9,10};//����ռ��ͬʱ��ʼ��
    p = new int [5];//���������ݿռ�
                    //p = new [5] int�����Ǵ����
    for(int i = 0;i < 5;i ++)
    {
        p[i] = i;
    }

    for(int i=0;i < 5;i ++)
    {
        cout << p[i] << endl;
    }
    delete[] p; //delete p[]�����Ǵ����

    return 0;
}
