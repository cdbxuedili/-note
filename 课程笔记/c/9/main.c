#include <stdio.h>
#include <stdlib.h>


int main(int argc, const char *argv[])
{
	printf("argc:%d\n",argc);
	printf("argv[0]:%s\n",argv[0]);
	printf("argv[1]:%s\n",argv[1]);
	printf("argv[2]:%s\n",argv[2]);

	printf("%d\n",atoi(argv[1]));
	return 0;
}
