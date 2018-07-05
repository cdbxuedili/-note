#include <stdio.h>



int main(int argc, const char *argv[])
{
	char a = 0;
	scanf("%c",&a);
	switch(a)
	{
		case 'a':
			printf("11111\n");
			break;
		case 'b':
			printf("22222\n");
//			break;
		case 'c':
			printf("33333\n");
			break;
		default:
			printf("44444\n");
			break;

	}
	return 0;
}
