#include <stdio.h>
#include <time.h>
       #include <unistd.h>




int main(int argc, const char *argv[])
{
	char *weekday[] = {"星期日","星期一","星期二","星期三","星期四","星期五","星期六"};
	FILE* fp = NULL;
	time_t t;
	struct tm* p = NULL;
	fp = fopen("./log.txt","a");
	while(1)
	{
		//从1970 1月1日 0:0:0 到现在时间的秒数
		t = time(NULL);
		//ctime
		//周几 月份 日期 时分秒 年
	//	fprintf(fp,"%s\n",ctime(&t));
	
		p = localtime(&t);
		fprintf(fp,"%d-%d-%d %d:%d:%d %s\n",p->tm_year+1900,p->tm_mon+1
				,p->tm_mday,p->tm_hour,p->tm_min,p->tm_sec,weekday[p->tm_wday]);


		fflush(fp);
		sleep(1);
	}
	fclose(fp);
	return 0;
}
