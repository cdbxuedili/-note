#include <stdio.h>



int main(int argc, const char *argv[])
{
	int i,j;
	int a[6] = {64,23,5,17,82,9};
	int max;//假设最大值
	int flag;//记录真正最大值的下标
	int temp;

	for(i = 0;i < 5;i++)
	{
		max = a[i];
		flag = i;
		for(j = i+1;j < 6;j++)
		{
			if(max < a[j])
			{
				max = a[j];
				flag = j;
			}
		}
		temp = a[i];
		a[i] = a[flag];
		a[flag] = temp;
	}

	for(i = 0;i < 6;i++)
	{
		printf("%d ",a[i]);
	}
	
	printf("\n");
	return 0;
}
