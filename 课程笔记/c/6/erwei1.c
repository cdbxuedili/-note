#include <stdio.h>



int main(int argc, const char *argv[])
{
#if 0
	int a[3][4] = {1,2,3,4,5,6,7,8,9,10,11,12};
	int i,j;
	for(i = 0;i < 3;i++)
	{
		for(j = 0;j < 4;j++)
		{
			printf("%2d ",a[i][j]);
		}
		printf("\n");
	}
#endif
	int a[3][4];
	int i,j;
	for(i = 0;i < 3;i++)
	{
		for(j = 0;j < 4;j++)
		{
			scanf("%d",&a[i][j]);
		}
	}

#if 0
	for(i = 0;i < 3;i++)
	{
		for(j = 0;j < 4;j++)
		{
			printf("%2d ",a[i][j]);
		}
		printf("\n");
	}
#endif
	

	return 0;
}
