#include <stdio.h>



int main(int argc, const char *argv[])
{
	int a[2][3] = {1,2,3,4,5,6};
	int i,j;
	int num = 0;
	for(i = 0;i < 2;i++)
	{
		for(j = 0;j < 3;j++)
		{
			printf("a[%d][%d] = %d\n",i,j,a[i][j]);
			num += a[i][j]; 
		}
	}
	printf("num:%d\n",num);
	return 0;
}
