#include <stdio.h>



int main(int argc, const char *argv[])
{
	char *p = "hello";
//	*(p+1) = 'a';错误
	char buf[] = "hello";
	buf[1] = 'a';
	puts(buf);


	printf("buf:%p\n",buf);
	printf("p:%p\n",p);

	return 0;
}
