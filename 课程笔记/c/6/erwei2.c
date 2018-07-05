#include <stdio.h>



int main(int argc, const char *argv[])
{
	int a[3][4];
	printf("%d\n",sizeof(a));
	printf("%d\n",sizeof(int [3][4]));
	return 0;
}
