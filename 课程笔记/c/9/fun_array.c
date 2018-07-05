#include <stdio.h>

int fun(int m[],int n);
int fun1(int *p,int n);


int main(int argc, const char *argv[])
{
	int array[6];
	fun1(array,6);
	fun(array,6);

	return 0;
}

#if 0
int fun1(int m[],int n)
{
	int i;
	for(i = 0;i < n;i++)
	{
		scanf("%d",&m[i]);
	}
	return 0;
}

#endif

int fun1(int *p,int n)
{
	int i;
	for(i = 0;i < n;i++)
	{
//		printf("%d ",*(p+i));
		scanf("%d",p+i);
	}
	return 0;
}



int fun(int m[],int n)
{
	int i;
	for(i = 0;i < n;i++)
	{
		printf("%d ",m[i]);
	}
	printf("\n");
	return 0;
}
