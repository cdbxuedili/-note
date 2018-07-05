#include <stdio.h>



int main(int argc, const char *argv[])
{
	char ch = 0;
	int i,j,k;
	scanf("%c",&ch);
	if(ch < 'A' || ch > 'Z')
	{
		printf("输入的不是A~Z,退出!\n");
		return -1;
	}

	for(i = 0;i <= ch-'A';i++)
	{
		for(j = 0;j < i;j++)
		{
			printf("*");
		}
		for(k = 0;k < i+1;k++)
		{
			putchar(ch-k);
		}
		printf("\n");
	}

	return 0;
}
