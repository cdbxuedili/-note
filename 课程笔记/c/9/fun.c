#include <stdio.h>

int fun_add(int m,int n);

int main(int argc, const char *argv[])
{
	int a = 0,b = 0;
	int ret = 0;
	printf("请输入需要相加的两个整数a和b:\n");
	scanf("%d%d",&a,&b);
	ret  = fun_add(a,b);
	printf("a+b = %d\n",ret);
	return 0;
}

int fun_add(int m,int n)
{ 
#if 0
	int z;
	z = m+n;
	return z;
#endif
	return m+n;
}
