#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdlib.h>
#include <errno.h>

int mysem_init(int semid,int n,int value)
{
	//semctl第四个参数需要是 union semun 类型的一个变量
	union semun {
	       int		val;	/* Value for SETVAL */
	       struct semid_ds *buf;	/* Buffer for IPC_STAT, IPC_SET */
	       unsigned short  *array;	/* Array for GETALL, SETALL */
	       struct seminfo  *__buf;	/* Buffer for IPC_INFO
					   (Linux-specific) */
	   };

	   union semun buf;
	buf.val = value; // 设置信号量的初始值

	if(-1 == semctl(semid,n,SETVAL,buf))
	{
		perror("semctl");
		return -1;
	}
	
	return 0;
}

int mysem_wait(int semid,int n) 
{
	struct sembuf buf;
	
	buf.sem_num = n;  //等待第几个信号量
	buf.sem_op = -1;  //p操作 -1
	buf.sem_flg = SEM_UNDO;

	if(-1 == semop(semid,&buf,1))
	{
		perror("semop");
		return -1;
	}

	return 0;
}

int mysem_post(int semid,int n)
{
	struct sembuf buf;
	
	buf.sem_num = n;  //设置第几个信号量
	buf.sem_op = 1;  //v操作 +1
	buf.sem_flg = SEM_UNDO;

	if(-1 == semop(semid,&buf,1))
	{
		perror("semop");
		return -1;
	}

	return 0;
}



int main(int argc, const char *argv[])
{
	key_t key;
	int semid;

	key = ftok("/home/linux/",'a');

	if(key == -1)
	{
		perror("ftok");
		exit(1);
	}

	semid = semget(key,2,IPC_CREAT | IPC_EXCL | 0664);//打开或者创建一个信号灯集

	if(semid == -1)
	{
		if(errno != EEXIST)
		{
			perror("semget");
			exit(1);
		}
		else
		{
			semid = semget(key,2,0664);
		}
	}

	mysem_init(semid,0,1);//将第0个信号量的值初始化为1
	mysem_init(semid,1,0);//将第1个信号量的值初始化为0

	mysem_wait(semid,0);

	printf("hello\n");
	mysem_post(semid,1);
	mysem_wait(semid,1);

	printf("world\n");
	mysem_post(semid,0);

	return 0;
}
