#include <stdio.h>



int main(int argc, const char *argv[])
{
	int year = 0,month = 0,day = 0;
	int flag = 0;
	int data = 0;
	
	printf("请按照如下格式输入年月日,例如:2018-3-9\n");
	scanf("%d-%d-%d",&year,&month,&day);

	if(year%4 == 0 && year%100 != 0 || year%400 == 0)
	{
		flag = 1;
	}

	if(day < 1 || day > 31)
	{
		printf("输入天数有误,输入天数不应该大于31或者小于1!\n");
		return -1;
	}

	if(month == 2 || month == 4 || month == 6 || month == 9 || month == 11)
	{
		if(day > 30)
		{
			printf("输入月份为小月,天数不能大于30天!\n");
			return -1;
		}
	}

	if(month == 2 && flag == 1)
	{
		if(day > 29)
		{
			printf("输入年份为闰年,二月天数不能大于29天!\n");
			return -1;
		}
	}

	if(month == 2 && flag == 0)
	{
		if(day > 28)
		{
			printf("输入年份为平年,二月天数不能大于28天!\n");
			return -1;
		}
	}

	switch(month)
	{
		case 12:
			data = data + 30;
		case 11:
			data = data + 31;
		case 10:
			data = data + 30;
		case 9:
			data = data + 31;
		case 8:
			data = data + 31;
		case 7:
			data = data + 30;
		case 6:
			data = data + 31;
		case 5:
			data = data + 30;
		case 4:
			data = data + 31;
		case 3:
			data = data + 28 + flag;
		case 2:
			data = data + 31;
		case 1:
			data = data + day;
			break;
		default:
			printf("输入的月份有误,一年只有12个月!\n");
			return -1;
	}

	printf("输入的年月生日是%d年的第%d天\n",year,data);

	return 0;
}
