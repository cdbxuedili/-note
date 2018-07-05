#include <stdio.h>



int main(int argc, const char *argv[])
{
	int a[4][4] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
	int i,j;
	int temp = 0;

	for(i = 0;i < 4;i++)
	{
		for(j = 0;j < i;j++)
		{
			temp = a[i][j];
			a[i][j] = a[j][i];
			a[j][i] = temp;
		}
	}
	
	for(i = 0;i < 4;i++)
	{
		for(j = 0;j < 4;j++)
		{
			printf("%3d",a[i][j]);
		}
		printf("\n");
	}



	return 0;
}
