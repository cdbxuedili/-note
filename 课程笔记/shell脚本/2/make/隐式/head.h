#ifndef _HEAD_H_
#define _HEAD_H_

#include <stdio.h>
#include <stdlib.h>

typedef int DATATYPE;

typedef struct node
{
	DATATYPE data;
	struct node *next;
}LINKLIST;

extern LINKLIST *create_empty_linklist();
extern int insert_head_linklist(LINKLIST *L,DATATYPE data);
extern int insert_tail_linklist(LINKLIST *L,DATATYPE data);
extern int delete_assign_linklist(LINKLIST *L,DATATYPE data);
extern int print_linklist(LINKLIST *L);
#endif
