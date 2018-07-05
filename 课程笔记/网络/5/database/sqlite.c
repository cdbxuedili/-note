#include<stdio.h>
#include<sqlite3.h>

int my_first_callback(void *p,int n,char **f_value,char **f_name)
{
	int i;

	if(*(int *)p == 1)
	{
		for(i = 0;i < n;i ++)
		{
			printf("%s\t",f_name[i]);
		}
		*(int *)p = 0;
		printf("\n");
	}
	for(i = 0;i < n;i ++)
	{
		printf("%s\t",f_value[i]);
	}
	printf("\n");
	//	printf("小小的分割符\n");
	return 0;
}

int main(int argc, const char *argv[])
{
	sqlite3 *db;
	if(sqlite3_open("./my.db",&db) != SQLITE_OK)
	{
		printf("%s\n",sqlite3_errmsg(db));	
		return -1;
	}

	char optsql[128];
	char *errmsg;
	sprintf(optsql,"create table stu(name,score);");
	if(sqlite3_exec(db,optsql,NULL,NULL,&errmsg) != SQLITE_OK)
	{
		printf("%s\n",errmsg);
		return -1;
	}

	int i;

	char name[15];
	int score;
	for(i = 0;i < 3;i ++)
	{
		scanf("%s%d",name,&score);
		sprintf(optsql,"insert into stu values('%s',%d);",name,score);
		sqlite3_exec(db,optsql,NULL,NULL,NULL);
	}

	int ctl = 1;
	sprintf(optsql,"select * from stu;");
	sqlite3_exec(db,optsql,my_first_callback,&ctl,NULL);
	
	sprintf(optsql,"select * from stu where name='a';");
	char **result;
	int r;
	int c;
	int count = 0;
	sqlite3_get_table(db,optsql,&result,&r,&c,NULL);
	
	printf("r = %d,c = %d\n",r,c);
	for(i = 0;i < c;i ++)
	{
		printf("%s\t",result[i]);
	}
	printf("\n");

	for(i = c;i < c * (r + 1);i ++)
	{
		printf("%s\t",result[i]);
		count ++;

		if(count % c == 0)
			printf("\n");
	}

	return 0;

}
