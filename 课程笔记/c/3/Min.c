#include <stdio.h>

#define  Min(a,b)  ((a > b) ? (b) : (a))

int main(int argc, const char *argv[])
{
	int x = 10, y = 5;
	printf("%d\n",Min(x,y));
	return 0;
}
