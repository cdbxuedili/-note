#include <stdio.h>



int main(int argc, const char *argv[])
{
	int a = 10;
	char b = 5;
	short c = 15;
	int *p = &a;
	char *q = &b;
	short *z = &c;
	printf("%p\n",p);
	printf("%p\n",p+1);
	printf("%p\n",p);
	printf("%p\n",q);
	printf("%p\n",q+1);
	printf("%p\n",z);
	printf("%p\n",z+1);
	return 0;
}
