#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/ioctl.h>
#include"mpu6050.h"

int main(int argc, const char *argv[])
{
	int fd;
	union mpu6050 data;

	fd = open("/dev/mpu6050",O_RDWR);

	while(1)
	{
		ioctl(fd,GYRO_CMD,&data);
		printf("GYRO:x = %d,y = %d,z = %d\n",data.gyro.x,data.gyro.y,data.gyro.z);
		ioctl(fd,ACCEL_CMD,&data);
		printf("ACCEL:x = %d,y = %d,z = %d\n",data.accel.x,data.accel.y,data.accel.z);

		ioctl(fd,TEMP_CMD,&data);
		printf("TEMP:%d\n",data.temp);
		sleep(1);
	}
	return 0;
}
