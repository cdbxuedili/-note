#include <stdio.h>


int main(int argc, const char *argv[])
{
	int a = 0xac,b = 0123;
	printf("a:%x b:%o\n",a,b);
	printf("a:%#x b:%#o\n",a,b);
	return 0;
}
