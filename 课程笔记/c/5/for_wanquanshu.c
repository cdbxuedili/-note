#include <stdio.h>



int main(int argc, const char *argv[])
{
	int i,j;
	int sum = 0;
	for(i = 1;i <= 10000;i++)
	{
		for(j = 1,sum = 0;j <= i/2;j++)
		{
			if(i%j == 0)
			{ 
				sum = sum+j;
			}
		}
		if(sum == i)
		{
			printf("%d\n",i);
		}
	}
			
	return 0;
}
