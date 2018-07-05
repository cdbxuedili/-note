#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include "head.h"

int main(int argc, const char *argv[])
{
	int fd;

	fd = open("/dev/mpu6050",O_RDWR);
	
	union mpu6050 data;
	while(1)
	{
		ioctl(fd,ACCEL_CMD,&data);
		printf("accel:x = %x,y = %x,z = %x\n",data.accel.x,data.accel.y,data.accel.z);

		ioctl(fd,GYRO_CMD,&data);
		printf("gyro:x = %x,y = %x,z = %x\n",data.gyro.x,data.gyro.y,data.gyro.z);

		ioctl(fd,TEMP_CMD,&data);
		printf("temp:%x\n",data.temp);

		sleep(1);
	}
	return 0;
}
