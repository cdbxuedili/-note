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

	if(score >= 90)
	{
		printf("A\n");
	}
	else if(score >= 80)
	{
		printf("B\n");
	}
	else if(score >= 60)
	{
		printf("C\n");
	}
	else
	{
		printf("D\n");
	}

	return 0;
}
