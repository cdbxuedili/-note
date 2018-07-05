#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<string.h>
#include<sys/un.h>

int main(int argc, const char *argv[])
{
	int sockfd;
	struct sockaddr_un seraddr;

	if((sockfd = socket(AF_UNIX,SOCK_STREAM,0)) == -1)
	{
		perror("socket");
		exit(1);
	}

	memset(&seraddr,0,sizeof(seraddr));
	seraddr.sun_family = AF_UNIX;
	strcpy(seraddr.sun_path,"./s");

	int ser_len = sizeof(seraddr.sun_family) + strlen(seraddr.sun_path);

	if(connect(sockfd,(struct sockaddr *)&seraddr,ser_len) == -1)
	{
		perror("connect");
		exit(1);
	}

	char buf[64];
	while(1)
	{
		fgets(buf,sizeof(buf),stdin);
		buf[strlen(buf) - 1] = '\0';

		send(sockfd,buf,strlen(buf) + 1,0);

		recv(sockfd,buf,sizeof(buf),0);
		printf("%s\n",buf);
	}
	return 0;
}
