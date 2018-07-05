#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>

int main(int argc, const char *argv[])
{
	int sockfd;
	FILE *fp;
	sockfd = socket(AF_INET,SOCK_STREAM,0);

	struct sockaddr_in seraddr;
	memset(&seraddr,0,sizeof(seraddr));
	seraddr.sin_family = AF_INET;
	seraddr.sin_port = htons(atoi(argv[1]));
	seraddr.sin_addr.s_addr = inet_addr("172.25.1.194");

	if(connect(sockfd,(struct sockaddr *)&seraddr,sizeof(seraddr)) == -1)
	{
		perror("connect");
		return -1;
	}

	char buf[10];
	size_t n;
	fp = fopen("./1.txt","r");
	while(1)
	{
		n = fread(buf,1,sizeof(buf),fp);
		
		send(sockfd,buf,n,0);

		if(n < sizeof(buf))//最后一次读取
			break;
	}
	fclose(fp);
	close(sockfd);
	return 0;
}
