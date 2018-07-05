#include <stdio.h>

int fun(int m[][4],int n);
int fun(int (*p)[4],int n);


int main(int argc, const char *argv[])
{
	int a[3][4];//int [4] a[3]
	fun(a,3);
	fun1(a,3);//&a[0]
	return 0;
}

int fun(int m[][4],int n)
{
	int i,j;
	for(i = 0;i < n;i++)
	{
		for(j = 0;j < 4;j++)
		{
			scanf("%d",&m[i][j]);
		}
	}
	return 0;
}

int fun1(int (*p)[4],int n)
{
	int i,j;
	for(i = 0;i < n;i++)
	{
		for(j = 0;j < 4;j++)
		{
			printf("%2d ",p[i][j]);//*(*(p+i)+j)
		}
		printf("\n");
	}
	return 0;
}



