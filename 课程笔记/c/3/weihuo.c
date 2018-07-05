#include <stdio.h>



int main(int argc, const char *argv[])
{
	unsigned char x = 076,y = 0x89,z;
	z = x | y;
	printf("%d\n",z);
	return 0;
}
