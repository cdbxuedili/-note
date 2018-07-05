#include<linux/init.h>
#include<linux/module.h>
#include<linux/i2c.h>
#include<linux/cdev.h>
#include<linux/fs.h>
#include<linux/device.h>
#include<asm/uaccess.h>
#include"mpu6050.h"

#define MPU6050_MAJOR 500
#define MPU6050_MINOR 0

#define SMPLRT_DIV  0x19    //采样率分频，典型值：0x07(125Hz) */
#define CONFIG   0x1A       // 低通滤波频率，典型值：0x06(5Hz) */
#define GYRO_CONFIG  0x1B   // 陀螺仪自检及测量范围，典型值：0x18(不自检，2000deg/s) */
#define ACCEL_CONFIG 0x1C  // 加速计自检、测量范围及高通滤波频率，典型值：0x01(不自检，2G，5Hz) */
#define PWR_MGMT_1  0x6B // 电源管理，典型值：0x00(正常启用) */
#define WHO_AM_I  0x75 //IIC地址寄存器(默认数值0x68，只读) */

#define TEMP_OUT_H  0x41   // 存储的最近温度传感器的测量值 */
#define TEMP_OUT_L  0x42
 
#define GYRO_XOUT_H  0x43 // 存储最近的X轴、Y轴、Z轴陀螺仪感应器的测量值 */
#define GYRO_XOUT_L  0x44 
#define GYRO_YOUT_H  0x45
#define GYRO_YOUT_L  0x46
#define GYRO_ZOUT_H  0x47
#define GYRO_ZOUT_L  0x48

#define ACCEL_XOUT_H 0x3B  // 存储最近的X轴、Y轴、Z轴加速度感应器的测量值 */
#define ACCEL_XOUT_L 0x3C
#define ACCEL_YOUT_H 0x3D
#define ACCEL_YOUT_L 0x3E
#define ACCEL_ZOUT_H 0x3F
#define ACCEL_ZOUT_L 0x40


dev_t devno;

struct cdev mpu6050_cdev;

struct class *mpu6050_cls;
struct device *mpu6050_devs;

struct i2c_client *glo_client;

void mpu6050_write_data(unsigned char reg,unsigned char val)
{
	unsigned char tbuf[2] = {reg,val};
	struct i2c_msg msg[] = { //msg数组有几个元素由起始信号的个数决定
		{glo_client->addr,0,2,tbuf},
	};
	i2c_transfer(glo_client->adapter,msg,ARRAY_SIZE(msg));//由核心层提供给设备驱动层的一个接口，可以帮助设备驱动层操作
				   //总线驱动层中起始、应答、读写、结束等逻辑
}

unsigned char mpu6050_read_data(unsigned char reg)
{
	unsigned char twbuf[1] = {reg};
	unsigned char trbuf[1];//存放读出的数据
	struct i2c_msg msg[2] = {
		{glo_client->addr,0,1,twbuf},
		{glo_client->addr,1,1,trbuf},
	};

	i2c_transfer(glo_client->adapter,msg,ARRAY_SIZE(msg));

	return trbuf[0];
}

int mpu6050_open(struct inode *inode,struct file *filp)
{
	printk("mpu6050_open\n");
	return 0;
}

int mpu6050_close(struct inode *inode,struct file *filp)
{
	printk("mpu6050_close\n");
	return 0;
}

long mpu6050_ioctl(struct file *filp,unsigned int cmd,unsigned long arg)
{
	int ret;
	union mpu6050 data;
	switch(cmd)
	{
	case GYRO_CMD://读取加速度的信息
		data.gyro.x	= mpu6050_read_data(GYRO_XOUT_L);
		data.gyro.x	|= mpu6050_read_data(GYRO_XOUT_H) << 8;
		data.gyro.y	= mpu6050_read_data(GYRO_YOUT_L);
		data.gyro.y	|= mpu6050_read_data(GYRO_YOUT_H) << 8;
		data.gyro.z	= mpu6050_read_data(GYRO_ZOUT_L);
		data.gyro.z	|= mpu6050_read_data(GYRO_ZOUT_H) << 8;
		break;

	case ACCEL_CMD:
		data.accel.x = mpu6050_read_data(ACCEL_XOUT_L);
		data.accel.x |= mpu6050_read_data(ACCEL_XOUT_H) << 8;
		data.accel.y = mpu6050_read_data(ACCEL_YOUT_L);
		data.accel.y |= mpu6050_read_data(ACCEL_YOUT_H) << 8;
		data.accel.z = mpu6050_read_data(ACCEL_ZOUT_L);
		data.accel.z |= mpu6050_read_data(ACCEL_ZOUT_H) << 8;
		break;

	case TEMP_CMD:
		data.temp = mpu6050_read_data(TEMP_OUT_L);
		data.temp |= mpu6050_read_data(TEMP_OUT_H) << 8;
		break;
	}

	ret = copy_to_user((void *)arg,&data,sizeof(data));
	if(ret != 0)
	{

	}
	return 0;
}

struct file_operations mpu6050_ops = {
	.open = mpu6050_open,
	.release = mpu6050_close,
	.unlocked_ioctl = mpu6050_ioctl,
};

int mpu6050_probe(struct i2c_client *client,const struct i2c_device_id *id)
{
	int ret;

	glo_client = client;
	printk("match ok\n");

	devno = MKDEV(MPU6050_MAJOR,MPU6050_MINOR);
	
	ret = register_chrdev_region(devno,1,"mpu6050");
	cdev_init(&mpu6050_cdev,&mpu6050_ops);

	cdev_add(&mpu6050_cdev,devno,1);

	mpu6050_cls = class_create(THIS_MODULE,"mpu6050");
	mpu6050_devs = device_create(mpu6050_cls,NULL,devno,NULL,"mpu6050");
	
	mpu6050_write_data(SMPLRT_DIV,0x07);
	mpu6050_write_data(CONFIG,0x06);
	mpu6050_write_data(GYRO_CONFIG,0x18);
	mpu6050_write_data(ACCEL_CONFIG,0x01);
	mpu6050_write_data(PWR_MGMT_1,0x00);
	return 0;
}

int mpu6050_remove(struct i2c_client *client)
{
	device_destroy(mpu6050_cls,devno);
	class_destroy(mpu6050_cls);
	cdev_del(&mpu6050_cdev);
	unregister_chrdev_region(devno,1);
	printk("remove done\n");
	return 0;
}

struct of_device_id mpu6050_of_table[] = {
	{
		.compatible = "fs4412,mpu6050",
	},
	{},
};

struct i2c_device_id mpu6050_id_table[] = {
	{
		.name = "mympu6050",
	},
	{},
};

struct i2c_driver mpu6050_drv = {
	.driver = {
		.name = "mpu6050",//只是一个驱动名称,出现在sys/bus/i2c/drivers/mpu6050,不能省略
		.of_match_table = mpu6050_of_table,
	},

	.id_table = mpu6050_id_table,
	.probe = mpu6050_probe,
	.remove = mpu6050_remove,
};

int mpu6050_init(void)
{
	i2c_add_driver(&mpu6050_drv);
	printk("mpu6050_init\n");
	return 0;
}
module_init(mpu6050_init);

void mpu6050_exit(void)
{
	i2c_del_driver(&mpu6050_drv);
	printk("mpu6050_exit\n");
}
module_exit(mpu6050_exit);
MODULE_LICENSE("GPL");
