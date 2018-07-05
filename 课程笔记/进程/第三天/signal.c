#include <stdio.h>
#include <signal.h>
#include <stdlib.h>


int main(int argc, const char *argv[])
{
	sighandler_t sig;

	sig = signal(SIGINT,SIG_IGN); //声明当前进程遇到某个指定信号之后应该做什么操作（SIG_IGN是忽略）
	if(sig == SIG_ERR)
	{
		printf("fail\n");
		exit(1);
	}

	sleep(5);

	printf("hello\n");

	signal(SIGINT,SIG_DFL); //SIG_DFL为恢复为默认处理

	while(1);

	return 0;
}
