#include <stdio.h>



int main(int argc, const char *argv[])
{
	int num = 0;
	int numo = 0,numj = 0;
	int sumo = 0,sumj = 0;

	while(1)
	{
		if(1 != scanf("%d",&num))
		{
			getchar();
			continue;
		}

		if(num == 0)
		{
			break;
		}

		if(num%2 == 0)
		{
			numo++;
			sumo = sumo + num;
		}
		else
		{
			numj++;
			sumj = num + sumj;
		}
	}

	printf("奇数的个数为%d个,奇数和为%d\n",numj,sumj);
	printf("偶数的个数为%d个,偶数和为%d\n",numo,sumo);

	return 0;
}
