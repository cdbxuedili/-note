#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>

void fun(int signum)
{
	
}

typedef struct shmeory
{
	pid_t pidrcv;
	pid_t pidsnd;
	char buf[128];
}SHM;


int main(int argc, const char *argv[])
{
	key_t key;
	int shmid;

	signal(SIGUSR2,fun);

	key = ftok("/home/linux/xie/",'a');

	if(key == -1)
	{
		perror("ftok");
		exit(1);
	}

	shmid = shmget(key,sizeof(SHM),IPC_CREAT |IPC_EXCL | 0664);

	if(-1 == shmid)
	{
		if(errno != EEXIST)
		{
			perror("shmget");
			exit(1);
		}
		else
		{
			shmid = shmget(key,sizeof(SHM),0664);
		}
	}

	SHM *shm = shmat(shmid,NULL,0);
	
	if(shm == (void *)-1)
	{
		perror("shmat");
		exit(1);
	}
		shm->pidrcv = getpid();

	while(1)
	{
	
		pause();
		printf("%s\n",shm->buf);
		printf("%d\n",shm->pidsnd);
		printf("%d\n",shm->pidrcv);

		kill(shm->pidsnd,SIGUSR1);
		if(strncmp(shm->buf,"quit",4) == 0)
		{
			break;
		}
			
	}

	if(-1 == shmdt(shm))
	{
		perror("shmdt");
		exit(1);
	}

	sleep(1);

	if(-1 == shmctl(shmid,IPC_RMID,NULL))
	{
		perror("shmctl");
		exit(1);
	}


	return 0;
}
