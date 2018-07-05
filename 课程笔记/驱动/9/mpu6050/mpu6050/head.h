
union mpu6050
{
	struct accel 
	{
		unsigned short x;
		unsigned short y;
		unsigned short z;
	}accel;

	struct gyro
	{
		unsigned short x;
		unsigned short y;
		unsigned short z;
	}gyro;

	unsigned short temp;
};

#define ACCEL_CMD 	_IOR('x',0,union mpu6050)
#define GYRO_CMD 	_IOR('x',1,union mpu6050)
#define TEMP_CMD 	_IOR('x',2,union mpu6050)
