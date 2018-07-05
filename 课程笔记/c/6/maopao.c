#include <stdio.h>



int main(int argc, const char *argv[])
{
	int i,j;
	int temp = 0;
	int a[6] = {12,23,6,84,32,57};
	for(i = 0;i < 5;i++)
	{
		for(j = 0;j < 5-i;j++)
		{
			if(a[j] > a[j+1])
			{
				temp = a[j];
				a[j] = a[j+1];
				a[j+1] = temp;
			}
		}
	}
	for(i = 0;i < 6;i++)
	{
		printf("%d ",a[i]);
	}
	printf("\n");
	return 0;
}
