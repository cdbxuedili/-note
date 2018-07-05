#include <stdio.h>



int main(int argc, const char *argv[])
{
	int a[6] = {1,2,3,4,5,6};
	int i;
	for(i = 0; i < 10;i++)
	{
		printf("a[%d]:%d\n",i,a[i]);
	}
	return 0;
}
