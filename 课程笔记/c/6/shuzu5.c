#include <stdio.h>



int main(int argc, const char *argv[])
{
	int b = 10;
	int a[6] = {1,2,b,4,5,6};
	int i;
	for(i = 0;i < 6;i++)
	{
		printf("%d\n",a[i]);
	}

	return 0;
}
