#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string.h>
#include<stdlib.h>

typedef struct node 
{
	struct sockaddr_in data;
	struct node *next;
}listnode;

typedef struct msg
{
	char type;
	char name[15];
	char buf[128];
}msg_t;

listnode *create_empty_linklist()
{
	listnode *head;

	head = (listnode *)malloc(sizeof(listnode));

	head->next = NULL;

	return head;
}

void user_login(listnode *head,struct sockaddr_in cliaddr,int sockfd,msg_t info)
{
	listnode *p = head->next;//ｐ就是头节点后面的第一个节点
	
	while(p != NULL)//此时刚刚登录的这个客户端在链表中还未存在
	{
		sendto(sockfd,&info,sizeof(info),0,(const struct sockaddr *)&p->data,sizeof(p->data));
		p = p->next;
	}

	p = (listnode *)malloc(sizeof(listnode));

	p->data = cliaddr;

	p->next = head->next;
	head->next = p;
}

void user_talk(listnode *head,struct sockaddr_in cliaddr,int sockfd,msg_t info)
{
	listnode *p = head->next;

	while(p != NULL)
	{
		if(memcmp(&cliaddr,&p->data,sizeof(cliaddr)) != 0)
			sendto(sockfd,&info,sizeof(info),0,(const struct sockaddr *)&p->data,sizeof(p->data));
		p = p->next;	
	}
}

void user_exit(listnode *head,struct sockaddr_in cliaddr,int sockfd,msg_t info)
{
	listnode *p = head;	
	listnode *q;
	while(p->next != NULL)
	{
		if(memcmp(&cliaddr,&p->next->data,sizeof(cliaddr)) == 0)
		{
			//删除节点
			q = p->next;
			p->next = q->next;
			
			free(q);
			q = NULL;
		}
		else 
		{
			sendto(sockfd,&info,sizeof(info),0,(const struct sockaddr *)&p->next->data,sizeof(p->next->data));
			p = p->next;
		}

	}
}

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
	
	listnode *head;
	head = create_empty_linklist();

	msg_t info;
	socklen_t len = sizeof(cliaddr);
	ssize_t ret;
	while(1)
	{
		ret = recvfrom(sockfd,&info,sizeof(info),0,(struct sockaddr *)&cliaddr,&len);
		printf("ret = %d,ip = %s\n",ret,inet_ntoa(cliaddr.sin_addr));
		printf("type = %c,name = %s\n",info.type,info.name);

		switch(info.type)
		{
		case 'L':
			user_login(head,cliaddr,sockfd,info);
			break;
		case 'T':
			user_talk(head,cliaddr,sockfd,info);
			break;
		case 'Q':
			user_exit(head,cliaddr,sockfd,info);
			break;
		}

	}

	return 0;
}
