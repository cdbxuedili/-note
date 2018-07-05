#include <stdio.h>




int main(int argc, const char *argv[])
{
	int a = 10,b = 5,c = 12;
	int x;
	x = (a = a+b,b = a-b,c = a+b);
	printf("%d\n",x);
	return 0;
}
