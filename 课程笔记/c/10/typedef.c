#include <stdio.h>
#if 0
#define 标识符 被替换的目标
注:本质是字符串的整体代换,不适合替换数据类型!!!

typedef 已知或已存在的数据类型  别名;  
注:typedef末尾有';'
功能:将已知或已存在的数据类型起别名
#endif

//#define A int
//#define B int [6]

typedef int A;
typedef int B[6];//typedef int [6] B;
typedef int (*C)[6];//typedef int (*)[6] C;
typedef int (*D)(int,int);//typedef int (*)(int,int) D;

int fun(int m,int n)
{
	return m+n;
}


int main(int argc, const char *argv[])
{
	A stu;
	B b = {1,2,3,4,5,6};
	C p = &b;
	D q = fun;
	int m = 10,n = 5;
	q(m,n);
	return 0;
}
