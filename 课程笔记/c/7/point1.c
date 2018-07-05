#include <stdio.h>



int main(int argc, const char *argv[])
{
	int a = 10;
	int *p = &a;
	*p = 20;//a = 20;
	printf("%d\n",a);
	printf("%d\n",*p);
	return 0;
}
