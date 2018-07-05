#include <stdio.h>



int main(int argc, const char *argv[])
{
	int a = 0;
	scanf("%d",&a);

	if(a > 100)
	{
		printf("a > 100\n");
	}
	else if( (a <= 100) && (a > 0))
	{
		printf("0 < a <= 100\n");
	}
	else
	{
		printf("a <= 0\n");
	}
	return 0;
}
