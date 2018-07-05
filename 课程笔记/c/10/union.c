#include <stdio.h>

union a
{
	char a;
	int b;
};
//union 共用体 ,里面成员共用同一片空间,空间大小向最大的数据类型看齐
//所以只能同时使用其中一个成员
//注:共用体union使用时需要先将空间初始化(用大的数据类型赋予0值做初始化)

int main(int argc, const char *argv[])
{
	union a  stu;
	stu.b = 0;
	stu.a = 10;
	printf("%d\n",sizeof(union a));
	printf("%d\n",stu.a);
	printf("%d\n",stu.b);
	return 0;
}
