#include <stdio.h>



int main(int argc, const char *argv[])
{
	int a = 10;
	int b = 0;
	b = a++ + ++a + a++;
	printf("b:%d\n",b);
	printf("a:%d\n",a);
	return 0;
}
