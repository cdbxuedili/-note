#include <stdio.h>



int main(int argc, const char *argv[])
{
	int a[6] = {1,2,3,4,5,6};
	int *p = a;
	int (*q)[6] = &a;//int [6]*p = &a;
	printf("q:%p\n",q);
	printf("p:%p\n",p);
	printf("p+1:%p\n",p+1);
	printf("q+1:%p\n",q+1);
	printf("%d\n",sizeof(int (*)[6]));
	return 0;
}
