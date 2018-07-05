#include <stdio.h>


int main(int argc, const char *argv[])
{
	int a = 10,b = 5;
	int c;
	c = (a < b) || (++a);
	printf("c:%d\n",c);
	printf("a:%d\n",a);

	return 0;
}
