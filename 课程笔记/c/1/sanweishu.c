#include <stdio.h>



int main(int argc, const char *argv[])
{
	int i,j,k;
	int sum = 0;
	for(i = 1;i < 5;i++)
	{
		for(j = 1;j < 5;j++)
		{
			for(k = 1;k < 5;k++)
			{
				if(i!=j&&j!=k&&i!=k)
				{
					printf("%d%d%d\n",i,j,k);
					sum++;
				}
			}
		}
	}
	printf("%d\n",sum);
	return 0;
}
