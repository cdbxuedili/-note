#include <stdio.h>



int main(int argc, const char *argv[])
{
	int a[6] = {1,2,3,4,5,6};
	int b[6] = {1,2,3,4,5,6};
	int c[6] = {1,2,3,4,5,6};
	int d[6] = {1,2,3,4,5,6};
	int e[6] = {1,2,3,4,5,6};
	int i;
	c[10] = 250;

	printf("a:********************\n");
	for(i = 0;i < 6;i++)
	{
		printf("%d ",a[i]);
	}
	printf("\n");

	printf("b:********************\n");
	for(i = 0;i < 6;i++)
	{
		printf("%d ",b[i]);
	}
	printf("\n");

	printf("c:********************\n");
	for(i = 0;i < 6;i++)
	{
		printf("%d ",c[i]);
	}
	printf("\n");

	printf("d:********************\n");
	for(i = 0;i < 6;i++)
	{
		printf("%d ",d[i]);
	}
	printf("\n");

	printf("e:********************\n");
	for(i = 0;i < 6;i++)
	{
		printf("%d ",e[i]);
	}
	printf("\n");
	return 0;
}
