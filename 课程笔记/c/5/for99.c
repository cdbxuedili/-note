#include <stdio.h>



int main(int argc, const char *argv[])
{
	int i,j;
	for(i = 0;i <= 9;i++)
	{
		for(j = 0;j <= 9;j++)
		{
			printf("%3d",i*10+j);
		}
		printf("\n"); 
	}
	return 0;
}
