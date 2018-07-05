#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

int main(int argc, const char *argv[])
{
	int sockfd;

	sockfd = socket(AF_INET,SOCK_DGRAM,0);

	struct sockaddr_in multiaddr;
	multiaddr.sin_family = AF_INET;
	multiaddr.sin_port = htons(50000);
	multiaddr.sin_addr.s_addr = inet_addr("224.1.2.3");

	while(1)
	{
		sendto(sockfd,"hello",5,0,(struct sockaddr *)&multiaddr,sizeof(multiaddr));
		sleep(1);
	}
	return 0;
}
