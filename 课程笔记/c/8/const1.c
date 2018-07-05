#include <stdio.h>



int main(int argc, const char *argv[])
{
	int a = 10;
	int b = 5;
	int * const p = &a;
	int **q = &p;
	*q = &b;
//	p = &b;
//	*p = 20;
	printf("*p:%d\n",*p);
	return 0;
}
