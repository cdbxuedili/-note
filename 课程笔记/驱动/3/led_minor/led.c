#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <asm/io.h>
#include "head.h"

#define GPX2CON 0x11000c40
#define GPX1CON 0x11000c20
#define GPF3CON 0x114001e0

unsigned int *gpx2con;
unsigned int *gpx2dat;
unsigned int *gpx1con;
unsigned int *gpx1dat;
unsigned int *gpf3con;
unsigned int *gpf3dat;

int led_major;
struct class *led_cls;
struct device *led_devs;


static int fs4412_led_open(struct inode *inode,struct file *filp)
{
	int led_minor;

	led_minor = iminor(inode);

	filp->private_data = (void *)led_minor;
	return 0;
}

void led_on(int num)
{
	switch(num)
	{
	case 0:
		writel((readl(gpx2dat) & ~(1 << 7)) | 1 << 7,gpx2dat);
		break;
	case 1:
		writel((readl(gpx1dat) & ~(1 << 0)) | 1 << 0,gpx1dat);
		break;
	case 2:
		writel((readl(gpf3dat) & ~(1 << 4)) | 1 << 4,gpf3dat);
		break;
	case 3:
		writel((readl(gpf3dat) & ~(1 << 5)) | 1 << 5,gpf3dat);
		break;
	}
}

void led_off(int num)
{
	switch(num)
	{
	case 0:
		writel((readl(gpx2dat) & ~(1 << 7)) ,gpx2dat);
		break;
	case 1:
		writel((readl(gpx1dat) & ~(1 << 0)) ,gpx1dat);
		break;
	case 2:
		writel((readl(gpf3dat) & ~(1 << 4)) ,gpf3dat);
		break;
	case 3:
		writel((readl(gpf3dat) & ~(1 << 5)) ,gpf3dat);
		break;

	}
}

static long fs4412_led_ioctl(struct file *filp,unsigned int cmd,unsigned long arg)
{
	int num;
	num = (unsigned int)filp->private_data;
	switch(cmd)
	{
	case LED_ON:
		led_on(num);
		break;
	case LED_OFF:
		led_off(num);
		break;
	}
	return 0;
}

struct file_operations led_ops = {
	.owner = THIS_MODULE,
	.open = fs4412_led_open,
	.unlocked_ioctl = fs4412_led_ioctl,
};

static int __init fs4412_led_init(void)
{
	int i;
	led_major = register_chrdev(0,"led",&led_ops);
	led_cls = class_create(THIS_MODULE,"led");

	for(i = 0;i < 4;i ++)
		led_devs = device_create(led_cls,NULL,MKDEV(led_major,i),NULL,"led%d",i);

	gpx2con = ioremap(GPX2CON,4);
	gpx2dat = gpx2con + 1;

	gpx1con = ioremap(GPX1CON,4);
	gpx1dat = gpx1con + 1;

	gpf3con = ioremap(GPF3CON,4);
	gpf3dat = gpf3con + 1;

	//led引脚设置为输出模式
	writel((readl(gpx2con) & ~(0xf << 28)) | 1 << 28,gpx2con);
	writel((readl(gpx1con) & ~(0xf << 0)) | 1 << 0,gpx1con);
	writel((readl(gpf3con) & ~(0xff << 16)) | 0x11 << 16,gpf3con);
	return 0;
}
module_init(fs4412_led_init);

static void __exit fs4412_led_exit(void)
{
	int i;
	for(i = 3;i >= 0;i --)
		device_destroy(led_cls,MKDEV(led_major,i));
	class_destroy(led_cls);
	unregister_chrdev(led_major,"led");
	return;
}
module_exit(fs4412_led_exit);
MODULE_LICENSE("GPL");
