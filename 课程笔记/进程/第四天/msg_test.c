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
	MSG msg1;
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

	msg.mtype = 100;//设置发送消息的类型

	while(1)
	{

		bzero(msg.buf,sizeof(msg.buf));//清空数组

		fgets(msg.buf,sizeof(msg.buf),stdin);//从键盘上获取字符串写入msg.buf

		msg.buf[strlen(msg.buf) - 1] = '\0';

		rv = msgsnd(msgid,&msg,sizeof(MSG) - sizeof(long),0);//向指定的消息队列发送消息


		if(rv == -1)
		{
			perror("msgsnd");
			exit(1);
		}

		//从消息队列中读取消息内容
		rv = msgrcv(msgid,&msg1,sizeof(MSG) - sizeof(long),100,0);

		if(rv == -1)
		{
			perror("msgrcv");
			exit(1);
		}

		printf("%s\n",msg1.buf);
	}
	return 0;
}
