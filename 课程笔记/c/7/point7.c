#include <stdio.h>



int main(int argc, const char *argv[])
{
	int a = 10;
	char b = 5;
	int *p = &a;
	char *q = &b;
	printf("%d %d\n",sizeof(char *),sizeof(q));
	printf("%d %d\n",sizeof(int *),sizeof(p));
	return 0;
}
