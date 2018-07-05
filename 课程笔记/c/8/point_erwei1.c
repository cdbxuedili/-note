#include <stdio.h>



int main(int argc, const char *argv[])
{
	int  a[3][4] = {1,2,3,4,5,6,7,8,9,10,11,12};

	int (*p)[4] = a;//int [4]*p = a;//&a[0]   int [4]
	printf("p:%p\n",p);
	printf("a:%p\n",a);
	printf("*(*(p+1)+1):%d\n",*(*(p+1)+1));
	printf("p[1][1]:%d\n",p[1][1]);
	printf("a[1][1]:%d\n",a[1][1]);
	return 0;
}
