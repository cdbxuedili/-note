#include <stdio.h>



int main(int argc, const char *argv[])
{
	int a[6] = {1,2,3,4,5,6};
	int b[6];

//	b = a;错误
	b[0] = a[0];
	b[1] = a[1];


	return 0;
}
