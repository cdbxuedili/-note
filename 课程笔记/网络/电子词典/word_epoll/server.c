#include "head.h"

void do_register(int connfd, MSG *pbuf, sqlite3 *db)
{
	char sqlstr[128];
	char *errmsg;

	char **result;
	int nrow;
	int ncolumn;
	sprintf(sqlstr,"select * from usr where name='%s';",pbuf->name);
	if(sqlite3_get_table(db,sqlstr,&result,&nrow,&ncolumn,&errmsg) != SQLITE_OK)
	{
		puts(errmsg);
		sqlite3_free(errmsg);
	}

	if(nrow >= 1)
	{
		pbuf->flag = FALSE;
	}
	else 
	{
		sprintf(sqlstr,"insert into usr values ('%s','%s');",pbuf->name,pbuf->data);

		if(SQLITE_OK != sqlite3_exec(db,sqlstr,NULL,NULL,&errmsg))
		{
			puts(errmsg);
			sqlite3_free(errmsg);
		}
		pbuf->flag = TRUE;
	}
	send(connfd, pbuf, sizeof(MSG), 0);
	return;
}

/******************************************************************************/

void do_login(int connfd, MSG *pbuf, sqlite3 *db)
{
	char sqlstr[128];
	char *errmsg, **result;
	int nrow, ncolumn;
	int i;
	int count = 0;
#if 0
	sprintf(sqlstr, "select * from usr;");
	if (sqlite3_get_table(db, sqlstr, &result, &nrow, &ncolumn, &errmsg) != SQLITE_OK)
	{
		puts(errmsg);
		sqlite3_free(errmsg);
	}
	printf("nrow = %d\n",nrow);	

	for(i = ncolumn;i < (nrow + 1) * ncolumn;i += ncolumn)
	{
		if(strcmp(result[i],pbuf->name) == 0 && strcmp(result[i + 1],pbuf->data) == 0)
			count ++;
	}
	if(count == 0)
	{
		pbuf->flag = FALSE;
	}
	else 
	{
		pbuf->flag = TRUE;
	}
	send(connfd, pbuf, sizeof(MSG), 0);
#endif 

	sprintf(sqlstr, "select * from usr where name='%s' and passwd='%s';",pbuf->name,pbuf->data);
	if (sqlite3_get_table(db, sqlstr, &result, &nrow, &ncolumn, &errmsg) != SQLITE_OK)
	{
		puts(errmsg);
		sqlite3_free(errmsg);
	}
	printf("nrow = %d\n",nrow);	

	if(nrow == 0)
	{
		pbuf->flag = FALSE;
	}
	else 
	{
		pbuf->flag = TRUE;
	}
	send(connfd,pbuf,sizeof(MSG),0);
	sqlite3_free_table(result);

	return;
}

/******************************************************************************/

void get_date(char date[])
{
	time_t t;
	struct tm *tp;

	time(&t);
	
	tp = localtime(&t);
	
	sprintf(date, "%d-%02d-%02d %02d:%02d:%02d", tp->tm_year+1900, 
			tp->tm_mon+1, tp->tm_mday, tp->tm_hour, tp->tm_min, tp->tm_sec);

	return;
}

int do_searchword(int connfd, MSG *pbuf)
{
	FILE *fp;
	char line[300];
	char *p;
	int len, result;

	len = strlen(pbuf->data);
	if ((fp = fopen("dict.txt","r")) == NULL)
	{
		strcpy(pbuf->data, "dict on server can't be opened :");
		send(connfd, pbuf, sizeof(MSG), 0);
	}
	printf("query word is %s\n", pbuf->data);
	while (fgets(line, 300, fp) != NULL)
	{
		result = strncmp(pbuf->data, line, len);
		if (result > 0) 
			continue;
		if (result < 0 || line[len] != ' ') 
			break;
						
		p = line + len;
		while (*p == ' ') 
			p++; 
		strcpy(pbuf->data, p);
		fclose(fp);
		return 1;
	}
	fclose(fp);

	return 0;
}

void do_query(int connfd, MSG *pbuf, sqlite3 *db)
{
	char sqlstr[128], *errmsg;
	int len, result, found = 0;
	char date[64], word[64];
			
	strcpy(word, pbuf->data);
	found = do_searchword(connfd, pbuf);
	if (found)
	{
		get_date(date);
#if 0
		sprintf(sqlstr,"create table record (name,date,word);");
		if(SQLITE_OK != sqlite3_exec(db,sqlstr,NULL,NULL,&errmsg))
		{
			puts(errmsg);
			sqlite3_free(errmsg);
		}
#endif
		sprintf(sqlstr, "insert into record values ('%s', '%s', '%s');", pbuf->name, date, word);
		if (sqlite3_exec(db, sqlstr, NULL, NULL, &errmsg) != SQLITE_OK)
		{
			printf("error : %s\n", errmsg);
			sqlite3_free(errmsg);
		}
	}
	else
	{
		strcpy(pbuf->data, "not found\n");
	}
	send(connfd, pbuf, sizeof(MSG), 0);

	return;
}

/***************************************************************************/

int history_callback(void *arg, int f_num, char **f_value, char **f_name)
{
	int connfd;
	MSG buf;

	connfd = *(int *)arg;
	sprintf(buf.data, "%s : %s", f_value[1],f_value[2]);
	send(connfd, &buf, sizeof(buf),0);

	return 0;
}

void do_history(int connfd, MSG *pbuf, sqlite3 *db)
{
	char sqlstr[128], *errmsg;

	sprintf(sqlstr, "select * from record where name = '%s'", pbuf->name);
	if (sqlite3_exec(db, sqlstr, history_callback, &connfd, &errmsg) != SQLITE_OK)
	{
		printf("error : %s\n", errmsg);
		sqlite3_free(errmsg);
	}
	pbuf->data[0] = '\0';
	send(connfd, pbuf, sizeof(MSG), 0);
	
	return;
}

/******************************************************************************/

int main(int argc, const char *argv[])
{
	if(argc < 2)
	{
		printf("input error\n");
		return -1;
	}
	int sockfd;
	sqlite3 *db;
	if (sqlite3_open(DATABASE, &db) != SQLITE_OK)
	{
		printf("error : %s\n", sqlite3_errmsg(db));
		exit(-1);
	}

	sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd == -1)
	{

	}

	struct sockaddr_in seraddr,cliaddr;

	seraddr.sin_family = AF_INET;
	seraddr.sin_port = htons(atoi(argv[1]));
	seraddr.sin_addr.s_addr = inet_addr("172.25.1.194");
	
	if(bind(sockfd,(struct sockaddr *)&seraddr,sizeof(seraddr)) == -1)
	{
		perror("bind");
		return -1;
	}
	
	if(listen(sockfd,5) == -1)
	{
		perror("listen");
		return -1;
	}

	int epollfd;
	epollfd = epoll_create(50);
	if(epollfd == -1)
	{
		perror("epoll_create");
		return -1;
	}

	struct epoll_event ev;
	ev.data.fd = sockfd;
	ev.events = EPOLLIN;
	epoll_ctl(epollfd,EPOLL_CTL_ADD,sockfd,&ev);

	struct epoll_event events[50];
	int nfds;
	int i;
	int connfd;
	MSG buf;
	int len = sizeof(cliaddr);
	int recv_n;
	while(1)
	{
		nfds = epoll_wait(epollfd,events,50,-1);
		
		for(i = 0;i < nfds;i ++)
		{
			if(events[i].data.fd == sockfd)
			{
				connfd = accept(sockfd,(struct sockaddr *)&cliaddr,&len);	
				if(connfd == -1)
				{
					perror("accept");
				}

				ev.data.fd = connfd;
				ev.events = EPOLLIN;
				epoll_ctl(epollfd,EPOLL_CTL_ADD,connfd,&ev);
			}
			else//用来收发数据 
			{
				memset(&buf,0,sizeof(buf));
				recv_n = recv(events[i].data.fd,&buf,sizeof(buf),0);
				if(recv_n == -1)
				{
					perror("recv");
				}
				if(recv_n == 0)
				{
					printf("客户端退出\n");
					epoll_ctl(epollfd,EPOLL_CTL_DEL,events[i].data.fd,NULL);
					close(events[i].data.fd);
					continue;
				}
				if(recv_n > 0)
				{
					switch (buf.type)
					{
					case R :
						do_register(events[i].data.fd, &buf, db);
						break;
					case L :
						do_login(events[i].data.fd, &buf, db);
						break;
					case Q :
						do_query(events[i].data.fd, &buf, db);
						break;
					case H :
						do_history(events[i].data.fd, &buf, db);
						break;
					}

				}
			}
		}

	}
	return 0;
}
