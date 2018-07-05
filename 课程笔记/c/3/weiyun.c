#include <stdio.h>



int main(int argc, const char *argv[])
{
	unsigned char x = 0126,y = 0xac,z;
	z = x & y;
	printf("%d\n",z);
	return 0;
}
