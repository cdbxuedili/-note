#include <stdio.h>


struct a
{
	int b;
	int c;
}d = {10,5};//结构体全局变量

typedef struct
{
	int a;
	int b;
}stu_t;//这种结构体只能使用别名



int main(int argc, const char *argv[])
{
	printf("%d %d\n",d.b,d.c);
	return 0;
}
