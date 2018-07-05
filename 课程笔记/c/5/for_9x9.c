#include <stdio.h>



int main(int argc, const char *argv[])
{
	int i,j;
	for(i = 1;i <= 9;i++)
	{
		for(j = 1;j <= i;j++)
		{
			printf("%2dx%d=%-2d",i,j,i*j);
		}
		printf("\n");
	}
	return 0;
}
