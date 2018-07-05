#include <stdio.h>



int main(int argc, const char *argv[])
{
	const int a = 10;
//	a = 20;
	int *p = &a;
	*p = 20;
	printf("%d\n",a);
	return 0;
}
