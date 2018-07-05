#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

typedef struct msgbuf
{
	long mtype;
	char buf[128];
}MSG;

int main(int argc, const char *argv[])
{

	key_t key;
	int msgid;
	MSG msg;
	int rv;

	key = ftok("/home/linux/",'a');//获取key值

	if(key == -1)
	{
		perror("ftok");
		exit(1);
	}

	msgid = msgget(key,IPC_CREAT | IPC_EXCL | 0664);//打开或者创建消息队列


	if(msgid == -1)
	{
		if(errno != EEXIST)//如果该消息队列存在重新打开

		{
			perror("msgget");
			exit(1);
		}
		else
		{
			msgid = msgget(key,0664);
		}
	}


	while(1)
	{
		rv = msgrcv(msgid,&msg,sizeof(MSG) - sizeof(long),100,0);

		if(rv == -1)
		{
			perror("msgrcv");
			exit(1);
		}

		printf("%s\n",msg.buf);

		if(0 == strncmp(msg.buf,"quit",4))
		{
			break;
		}
	}
	return 0;
}
