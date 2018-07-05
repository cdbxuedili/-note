#include <stdio.h>



int main(int argc, const char *argv[])
{
	int a;
	char b;
	int c;
	printf("请输入以下三个数据格式为int char int:\n");
//	scanf("%d%c%d",&a,&b,&c);
//1.scanf("%c%d%d",&b,&a,&c);
//2.scanf("%d %c%d",&a,&b,&c);
//3.scanf("%d%*c%c%d",&a,&b,&c);
	printf("a:%d b:%c c:%d\n",a,b,c);
	return 0;
}
