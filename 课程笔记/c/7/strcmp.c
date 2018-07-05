#include <stdio.h>
#include <string.h>


int main(int argc, const char *argv[])
{
	char s1[] = "hello";
//	char s2[] = "hella";
//  char s2[] = "hellz";
	char s2[] = "hello";
	printf("%d\n",strcmp(s1,s2));
	return 0;
}
