#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, const char *argv[])
{
	int sockfd;

	sockfd = socket(AF_INET,SOCK_DGRAM,0);
	if(sockfd == -1)
	{
		perror("socket");
		exit(1);
	}

	struct sockaddr_in seraddr,cliaddr;

	memset(&seraddr,0,sizeof(seraddr));
	seraddr.sin_family = AF_INET;
	seraddr.sin_port = htons(50000);
	seraddr.sin_addr.s_addr = inet_addr("172.25.1.194");//服务器的ip地址，对方的

#if 0	
	memset(&cliaddr,0,sizeof(cliaddr));
	cliaddr.sin_family = AF_INET;
	cliaddr.sin_port = htons(50001);
	cliaddr.sin_addr.s_addr = inet_addr("172.25.1.194");//自己的ip地址

	if(bind(sockfd,(const struct sockaddr *)&cliaddr,sizeof(cliaddr)) == -1)
	{
		perror("bind");
		exit(1);
	}
#endif
	char buf[10];
	socklen_t len = sizeof(seraddr);
	while(1)
	{
		fgets(buf,sizeof(buf),stdin);
		buf[strlen(buf) - 1] = '\0';//去掉\n
		
		sendto(sockfd,buf,strlen(buf) + 1,0,(const struct sockaddr *)&seraddr,len);

		if(strncmp(buf,"quit",4) == 0)
			break;
	}

	close(sockfd);
	return 0;
}
