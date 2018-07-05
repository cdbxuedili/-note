#include <stdio.h>



int main(int argc, const char *argv[])
{
	int a[6];
	int *p = &a[1];
	int *q = &a[4];
	printf("%d\n",q-p);
	return 0;
}
