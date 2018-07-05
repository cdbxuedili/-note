#include <stdio.h>



int main(int argc, const char *argv[])
{
	int i;
	int sum;
#if 0
	for(i = 1;i <= 100;i++)
	{
		sum = sum + i;
	}
#endif
	for(i = 1,sum = 0;i <= 100;sum = sum+i,i++)
	{
		;
	}


	printf("sum:%d\n",sum);
	return 0;
}
