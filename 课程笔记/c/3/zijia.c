#include <stdio.h>



int main(int argc, const char *argv[])
{
	int a = 10;
	int b;
	b = a++;
	printf("a:%d\n",a);
	printf("b:%d\n",b);

	return 0;
}
