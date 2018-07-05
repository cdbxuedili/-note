#include <stdio.h>



int main(int argc, const char *argv[])
{
	char a[] = "hello";
	char a1[] = {"hello"};
	char a2[] = {'h','e','l','l','o','\0'};
	char a3[] = {'h','e','l','l','o'};
//	char b[5] = "hello";  '\0'越界
	char b1[128] = "hello";//后面空间中均为'\0'

	printf("a:%d a1:%d a2:%d a3:%d\n",
			sizeof(a),sizeof(a1),sizeof(a2),sizeof(a3));
	return 0;
}
