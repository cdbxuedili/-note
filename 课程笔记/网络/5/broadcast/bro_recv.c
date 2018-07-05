#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>

int main(int argc, const char *argv[])
{
	int sockfd;

	sockfd = socket(AF_INET,SOCK_DGRAM,0);

	struct sockaddr_in seraddr,cliaddr;

	memset(&seraddr,0,sizeof(seraddr));
	seraddr.sin_family = AF_INET;
	seraddr.sin_port = htons(50000);
	seraddr.sin_addr.s_addr = inet_addr("172.25.1.255");

	bind(sockfd,(struct sockaddr *)&seraddr,sizeof(seraddr));

	char buf[10] = {0};
	int len = sizeof(cliaddr);
	while(1)
	{
		recvfrom(sockfd,buf,sizeof(buf),0,NULL,NULL);
		printf("buf = %s\n",buf);
	}

	return 0;
}
