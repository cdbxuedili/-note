#include <stdio.h>



int main(int argc, const char *argv[])
{
	int a = 10,b = 5,c = 15;
	int z;
	z = ((a < b) ? (a = a+b) : (b = a+c));
	printf("%d\n",z);
	return 0;
}
