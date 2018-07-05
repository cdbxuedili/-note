#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <errno.h>

typedef struct shmeory
{
	char buf[128];
}SHM;


int main(int argc, const char *argv[])
{
	key_t key;
	int shmid;

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

	printf("%s\n",shm->buf);

	return 0;
}
