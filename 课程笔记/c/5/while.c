#include <stdio.h>



int main(int argc, const char *argv[])
{
	int i = 1;
	int sum = 0;
	while(i <= 100)	
	{
		sum = i + sum;
		i++;
	}
	printf("%d\n",sum);
	return 0;
}

