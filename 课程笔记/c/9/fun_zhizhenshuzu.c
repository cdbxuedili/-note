#include <stdio.h>

int fun(int *m[],int n);
int fun1(int **p,int n);

int main(int argc, const char *argv[])
{
	int a[3];
	int *b[3] = {&a[0],&a[1],&a[2]};
	fun(b,3);
	fun1(b,3);
	return 0;
}

int fun(int *m[],int n)
{
	int i;
	for(i = 0;i < n;i++)
	{
		scanf("%d",m[i]);
	}
	return 0;
}

int fun1(int **p,int n)
{
	int i;
	for(i = 0;i < n;i++)
	{
		printf("%d\n",*p[i]);
	}
	return 0;
}


