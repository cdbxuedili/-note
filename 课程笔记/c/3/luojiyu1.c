#include <stdio.h>



int main(int argc, const char *argv[])
{
	int a = 10;
	int b = 5;
	int c;
	c = (a < b) && (++a) ;
	printf("a:%d\n",a);
	printf("c:%d\n",c);
	return 0;
}
