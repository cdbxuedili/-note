#include <stdio.h>



int main(int argc, const char *argv[])
{
	int a = 10;
	int *p = &a;
	printf("%p\n",p);
	p++;
	printf("%p\n",p);

	return 0;
}
