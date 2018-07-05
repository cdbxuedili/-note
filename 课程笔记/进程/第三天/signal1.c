#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void fun(int signum)
{
	if(signum == SIGINT)
	{
		printf("xieyuxing\n");
	}
	else if(signum == SIGQUIT)
	{
		printf("xiepeng\n");
	}
}


int main(int argc, const char *argv[])
{
	
	signal(SIGINT,fun); //声明遇到该信号则执行对应的信号处理函数
	signal(SIGQUIT,fun); //声明遇到该信号则执行对应的信号处理函数


	while(1);

	return 0;
}
