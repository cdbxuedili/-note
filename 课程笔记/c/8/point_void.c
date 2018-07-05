#include <stdio.h>



int main(int argc, const char *argv[])
{
	int a = 10;
	char b = 5;
	void *p = NULL;

	p = &a;
//	p = &b;
	
	*(int *)p = 20;

	printf("%d\n",*(int *)p);


	return 0;
}
