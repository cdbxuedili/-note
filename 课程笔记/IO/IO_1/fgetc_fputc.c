#include <stdio.h>


int main(int argc, const char *argv[])
{
	int c = 0;
	c = fgetc(stdin);//getchar
	if(EOF == c)
	{
		fprintf(stderr,"fail to fgetc\n");
		return -1;
	}
	fputc(c,stdout);//putchar
	return 0;
}
