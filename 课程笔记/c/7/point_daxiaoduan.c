#include <stdio.h>



int main(int argc, const char *argv[])
{
#if 0
	int a = 0x12345678;
	char *p = (char *)&a;
	printf("%#x\n",*p);
	printf("%#x\n",*(p+1));
	printf("%#x\n",*(p+2));
	printf("%#x\n",*(p+3));
#endif
	int a = 0x12345678;
	int *p = &a;
	printf("%#x\n",*(char *)p);

	return 0;
}
