#include <stdio.h>
#include <string.h>

int fun(char buf[])
{
	printf("fun_sizeof:%d\n",sizeof(buf));//4
	printf("fun_strlen:%d\n",strlen(buf));//5
	return 0;
}

int main(int argc, const char *argv[])
{
	char buf[128] = "hello";
	fun(buf);
	printf("main_sizeof:%d\n",sizeof(buf));//128
	printf("main_strlen:%d\n",strlen(buf));//5
	return 0;
}
