#include <stdio.h>




int main(int argc, const char *argv[])
{
	int score = 0;
	printf("请输入一个分数:\n");
	scanf("%d",&score);
	if(score > 100 || score < 0)
	{
		printf("输入分数有误!退出\n");
		return -1;
	}

	if(score < 90)
	{
		if(score < 80)
		{
			if(score < 60)
			{
				printf("D\n");
			}
			else
			{
				printf("C\n");
			}
		}
		else
		{
			printf("B\n");
		}

	}	
	else
	{
		printf("A\n");
	}




	return 0;
}
