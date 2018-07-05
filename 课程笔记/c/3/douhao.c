#include <stdio.h>



int main(int argc, const char *argv[])
{
	int a,b,c;
	int x;
	x = (a = 10,b = 5,c = 12);
	printf("%d\n",x);
	return 0;
}
