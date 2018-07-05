#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, const char *argv[])
{
	int sockfd;

	sockfd = socket(AF_INET,SOCK_DGRAM,0);

	struct sockaddr_in seraddr,cliaddr;

	memset(&seraddr,0,sizeof(seraddr));
	seraddr.sin_family = AF_INET;
	seraddr.sin_port = htons(50000);
	seraddr.sin_addr.s_addr = inet_addr("172.25.1.194");

	bind(sockfd,(const struct sockaddr *)&seraddr,sizeof(seraddr));

	ssize_t n;
	char buf[10];
	socklen_t len;
	while(1)
	{
		memset(buf,0,sizeof(buf));
		n = recvfrom(sockfd,buf,sizeof(buf),0,(struct sockaddr *)&cliaddr,&len);
		if(strncmp(buf,"quit",4) == 0)
		{
			printf("%s客户端退出\n",inet_ntoa(cliaddr.sin_addr));
			continue;
		}
		printf("n = %d\n",n);
		printf("ip:%s,port:%d,data:%s\n",inet_ntoa(cliaddr.sin_addr),ntohs(cliaddr.sin_port),buf);

	}
	return 0;
}
