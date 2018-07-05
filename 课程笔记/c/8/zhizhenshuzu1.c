#include <stdio.h>



int main(int argc, const char *argv[])
{
	int a[3] = {1,2,3};
	int *b[3] = {&a[0],&a[1],&a[2]};

	int **p = b;//&b[0]
	int i;
	for(i = 0;i < 3;i++)
	{
		printf("%d\n",*p[i]);
	}
	return 0;
}
