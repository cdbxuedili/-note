#include <stdio.h>



int main(int argc, const char *argv[])
{
	int a[6] = {1,2,3,4,5,6};
	int *p = a;//&a[0]
	printf("p:%p\n",p);
	printf("a:%p\n",a);
	printf("&a[0]:%p\n",&a[0]);
	printf("p+1:%p\n",p+1);
	printf("a+1:%p\n",a+1);
	printf("&a[1]:%p\n",&a[1]);
	printf("*(p+1):%d\n",*(p+1));
	printf("*(a+1):%d\n",*(a+1));
	printf("*(&a[1]):%d\n",*(&a[1]));
	printf("a[1]:%d\n",a[1]);
	printf("p[1]:%d\n",p[1]);
	return 0;
}
