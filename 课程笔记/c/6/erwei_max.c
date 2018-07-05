#include <stdio.h>



int main(int argc, const char *argv[])
{
	int a[3][4] = {1,2,3,250,5,6,7,250,9,10,11,12};
	int max = a[0][0];

	int i,j;
	for(i = 0;i < 3;i++)
	{
		for(j = 0;j < 4;j++)
		{
			if(max < a[i][j])
			{
				max = a[i][j];
			}
		}
	}

	for(i = 0;i < 3;i++)
	{
		for(j = 0;j < 4;j++)
		{
			if(max == a[i][j])
			{
				printf("a[%d][%d]:%d\n",i,j,a[i][j]);
			}
		}
	}



	return 0;
}
