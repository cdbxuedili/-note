#include <stdio.h>



int main(int argc, const char *argv[])
{
	int a = 10;
	int b = 5;
	const int *p = &a;
//	*p = 20;
	p = &b;
	return 0;
}
