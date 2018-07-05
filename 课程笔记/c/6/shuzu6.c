#include <stdio.h>



int main(int argc, const char *argv[])
{
	int a[10];
	printf("%d\n",sizeof(a));
	printf("%d\n",sizeof(int [10]));
	return 0;
}
