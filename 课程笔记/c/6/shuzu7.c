#include <stdio.h>



int main(int argc, const char *argv[])
{
	int n = 10;
	int a[n];
	printf("%d\n",sizeof(a));
	n = 5;
	printf("%d\n",sizeof(a));
	return 0;
}
