#ifndef _HEAD_H
#define _HEAD_H

#define LIST 1
#define DOWN 2
#define FALSE 3
#define TRUE 4
typedef struct ftp_data
{
	int type;
	int flag;
	char data[128];
	char fname[15];
	size_t len;
}my_ftp_data_t;
#endif
