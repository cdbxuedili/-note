#include <stdio.h>



int main(int argc, const char *argv[])
{
	unsigned char x = 75,y = 0173,z;
	z = x ^ y;
	printf("%d\n",z);
	return 0;
}
