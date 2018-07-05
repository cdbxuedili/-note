#include <linux/init.h>
#include <linux/module.h>
#include <linux/i2c.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <asm/uaccess.h>
#include "head.h"

#define SMPLRT_DIV  0x19    //采样率分频，典型值：0x07(125Hz) */
#define CONFIG   0x1A       // 低通滤波频率，典型值：0x06(5Hz) */
#define GYRO_CONFIG  0x1B   // 陀螺仪自检及测量范围，典型值：0x18(不自检，2000deg/s) */
#define ACCEL_CONFIG 0x1C  // 加速计自检、测量范围及高通滤波频率，典型值：0x01(不自检，2G，5Hz) */
#define PWR_MGMT_1  0x6B // 电源管理，典型值：0x00(正常启用) */

//数据类寄存器
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


int major;
struct class *cls;
struct device *devs;
struct i2c_client *glo_client;

//write_data(1,2);
void write_data(unsigned char reg,unsigned char val)
{
	unsigned char wbuf[] = {reg,val};
	//看时序，有几个起始信号就有几个消息，也就有几个数组元素
	struct i2c_msg msg[1] = {
		[0] = {
			.addr = glo_client->addr,
			.flags = 0,
			.len = 2,//由时序决定，传递的数据的字节数
			.buf = wbuf,
		},
	};
	i2c_transfer(glo_client->adapter,msg,ARRAY_SIZE(msg));
}

unsigned char read_data(unsigned char reg)
{
	unsigned char wbuf[1] = {reg};
	unsigned char rbuf[1];
	struct i2c_msg msg[2] = {
		[0] = {
			.addr = glo_client->addr,
			.flags = 0,
			.len = 1,
			.buf = wbuf,
		},
		[1] = {
			.addr = glo_client->addr,
			.flags = 1,
			.len = 1,
			.buf = rbuf,//读取到的数据要存放到rbuf中
		},
	};

	i2c_transfer(glo_client->adapter,msg,ARRAY_SIZE(msg));
	return rbuf[0];
}

int mpu6050_open(struct inode *inode,struct file *filp)
{
	return 0;
}

long mpu6050_ioctl(struct file *filp,unsigned int cmd,unsigned long arg)
{
	int ret;
	union mpu6050 data;
	switch(cmd)
	{
	case ACCEL_CMD:
		data.accel.x = read_data(ACCEL_XOUT_L);
		data.accel.x |= read_data(ACCEL_XOUT_H) << 8;
		data.accel.y = read_data(ACCEL_YOUT_L);
		data.accel.y |= read_data(ACCEL_YOUT_H) << 8;
		data.accel.z = read_data(ACCEL_ZOUT_L);
		data.accel.z |= read_data(ACCEL_ZOUT_H) << 8;
		break;
	case GYRO_CMD:
		data.gyro.x = read_data(GYRO_XOUT_L);
		data.gyro.x |= read_data(GYRO_XOUT_H) << 8;
		data.gyro.y = read_data(GYRO_YOUT_L);
		data.gyro.y |= read_data(GYRO_YOUT_H) << 8;
		data.gyro.z = read_data(GYRO_ZOUT_L);
		data.gyro.z |= read_data(GYRO_ZOUT_H) << 8;
		break;

	case TEMP_CMD:
		data.temp = read_data(TEMP_OUT_L);
		data.temp |= read_data(TEMP_OUT_H) << 8;
		break;
	}

	ret = copy_to_user((void *)arg,&data,sizeof(data));
	if(ret != 0)
	{
		printk("copy_to_user fail\n");
		return -EFAULT;
	}
	return 0;
}

struct file_operations fops = {
	.owner = THIS_MODULE,
	.open = mpu6050_open,
	.unlocked_ioctl = mpu6050_ioctl,
};

int demo_probe(struct i2c_client *client,const struct i2c_device_id *id)
{
	printk("match ok\n");
	glo_client = client;
	major =  register_chrdev(0,"mpu6050",&fops);
	cls = class_create(THIS_MODULE,"mpu6050");
	devs = device_create(cls,NULL,MKDEV(major,0),NULL,"mpu6050");

	//写入数据到控制类寄存器(写_需要查看写时序)
	write_data(SMPLRT_DIV,0x07);
	write_data(CONFIG,0x06);
	write_data(GYRO_CONFIG,0x18);
	write_data(ACCEL_CONFIG,0x01);
	write_data(PWR_MGMT_1,0x00);
	return 0;
}
int demo_remove(struct i2c_client *client)
{
	device_destroy(cls,MKDEV(major,0));
	class_destroy(cls);
	unregister_chrdev(major,"mpu6050");
	return 0;
}

struct of_device_id demo_tbl[] = {
	{
		.compatible = "fs4412,mpu6050",
	},
	{},
};

struct i2c_device_id demo_id_tbl[] = {
	{
		.name = "18031",//name必须要有内容,但是内容是什么不重要(前提是和设备树匹配)
	},
};

struct i2c_driver drv = {
	.driver = {
		.name = "demo", //   /sys/bus/i2c/demo
		.of_match_table = demo_tbl,
	},	

	.probe = demo_probe,
	.remove = demo_remove,

	.id_table = demo_id_tbl,
};

#if 0
int __init demo_init(void)
{
	i2c_add_driver(&drv);
	return 0;
}
module_init(demo_init);

void __exit demo_exit(void)
{
	i2c_del_driver(&drv);
	return;
}
module_exit(demo_exit);
#endif

module_i2c_driver(drv);
MODULE_LICENSE("GPL");
