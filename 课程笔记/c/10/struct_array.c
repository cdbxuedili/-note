#include <stdio.h>

typedef struct student
{
	char name[128];
	int id;
	int age;
	float score;
}stu_t;


int main(int argc, const char *argv[])
{
//	stu_t a[3] = {{"小红",1,20,89.5},{"小明",2,21,90},{"小李",3,19,66}};
//  结构体数组初始化形式
	stu_t a[3];
	int i;

	for(i = 0;i < 3;i++)
	{
		scanf("%s%d%d%f",a[i].name,&a[i].id,&a[i].age,&a[i].score);
	}


	for(i = 0;i < 3;i++)
	{
		printf("name:%s id:%d age:%d score:%.1f\n"
				,a[i].name,a[i].id,a[i].age,a[i].score);
	}

	
	return 0;
}
