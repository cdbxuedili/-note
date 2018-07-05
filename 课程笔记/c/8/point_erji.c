#include <stdio.h>



int main(int argc, const char *argv[])
{
	int a = 10;
	int *p = &a;
	int **q = &p;

	printf("*q:%p\n",*q);
	printf("p:%p\n",p);
	printf("&a:%p\n",&a);

	printf("**q:%d\n",**q);
	printf("*p:%d\n",*p);
	printf("a:%d\n",a);
	return 0;
}
