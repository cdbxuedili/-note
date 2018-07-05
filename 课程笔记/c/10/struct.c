#include <stdio.h>
#include <string.h>


struct student//标签名 (仅仅是结构体名字)
{
	char name[128];     //填充结构体成员
	int id;
	int age;
	float score;
};   //注意末尾有';'
//结构体就是将现有的数据类型杂糅组成新的数据类型
//struct student == int   数据类型名


int main(int argc, const char *argv[])
{
	//struct student a;//结构体变量定义: 结构体类型  变量名	
	struct student a = {"小明",1,20,89.5};
	struct student b;
	b = a;//结构体变量之间可以相互赋值,需要保证结构体类型一致
	//结构体变量的初始化,并且需要一一对应成员赋值
	a.id = 2;
	strcpy(a.name,"小花");
	printf("name:%s id:%d age:%d score:%.1f\n"
			,a.name,a.id,a.age,a.score);
	printf("name:%s id:%d age:%d score:%.1f\n"
			,b.name,b.id,b.age,b.score);
	//结构体变量打印形式
	//结构体变量应用内部成员时需要通过:  结构体变量名.结构体成员名


	return 0;
}
