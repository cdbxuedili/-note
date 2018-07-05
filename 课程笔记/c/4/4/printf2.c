#include <stdio.h>




int main(int argc, const char *argv[])
{
	int a = 10;
	float b = 123.456;
	char c = 'A';
	int d = 0xac;
	int e = 0123;
#if 0
	printf("a:%d\n",a);
	printf("b:%f\n",b);
	printf("b:%e\n",b);
	printf("c:%c\n",c);
	printf("d:%x\n",d);
	printf("e:%o\n",e);
#endif
	printf("a:%d b:%f c:%c d:%x e:%o\n",a,b,c,d,e);


	return 0;
}
