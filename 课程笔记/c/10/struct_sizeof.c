#include <stdio.h>

typedef struct a
{
//	char a;
//	short c;
//	char d;
//	int b;
//	double e;
}a_t;

#if 0
1.结构体的内部对齐只会出现在结构体内成员数据类型不一致时
,小的数据类型向大的数据类型转换
2.计算结构体对齐时,自上向下进行分析,一旦出现不同
,小的数据类型向大的数据类型对齐,遵循4个字节为一个大单位,保证数据完整性

#endif

int main(int argc, const char *argv[])
{
	printf("%d\n",sizeof(a_t));
	return 0;
}
