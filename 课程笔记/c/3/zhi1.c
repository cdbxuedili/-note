#include <stdio.h>



int main(int argc, const char *argv[])
{
	char a = 10;
	char b;
	b = a | 1 << 4;
	printf("%d\n",b);
	return 0;
}
