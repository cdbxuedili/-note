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
	seraddr.sin_port = htons(50001);
	seraddr.sin_addr.s_addr = inet_addr("172.25.1.255");

	int on = 1;
	setsockopt(sockfd,SOL_SOCKET,SO_BROADCAST,&on,sizeof(on));//使能广播权限

	char buf[10];
	while(1)
	{
	//	fgets(buf,sizeof(buf),stdin);
		sendto(sockfd,"hello",5,0,(struct sockaddr *)&seraddr,sizeof(seraddr));
	}

	return 0;
}
