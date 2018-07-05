#include <stdio.h>
#include <string.h>



int main(int argc, const char *argv[])
{
	char buf[128];
	fgets(buf,sizeof(buf),stdin);
	if(buf[strlen(buf)-1] == '\n')
		buf[strlen(buf)-1] = '\0';
	
	printf("buf:%s\n",buf);
//	fputs(buf,stdout);
	return 0;
}
