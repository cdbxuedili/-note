#include <stdio.h>



int main(int argc, const char *argv[])
{
	int score = 0;
	printf("请输入一个分数:\n");
	scanf("%d",&score);
	if(score > 100 || score < 0)
	{
		printf("输入的分数有误,退出!\n");
		return -1;
	}
	
	score = score / 10;

	switch(score)
	{
	case 10:
	case 9:
		printf("A\n");
		break;
	case 8:
		printf("B\n");
		break;
	case 7:
	case 6:
		printf("C\n");
		break;
	default:
		printf("D\n");
		break;
	}



	return 0;
}
