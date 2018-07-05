#include<linux/module.h>
#include<linux/init.h>
#include<linux/platform_device.h>
#include"led.h"
#include<linux/cdev.h>
#include<linux/fs.h>
#include<linux/device.h>
#include<asm/io.h>


#define LED_MAJOR 500
#define LED_MINOR 0

volatile unsigned int *gpx2con;
volatile unsigned int *gpx2dat;
volatile unsigned int *gpx1con;
volatile unsigned int *gpx1dat;
volatile unsigned int *gpf3con;
volatile unsigned int *gpf3dat;

MODULE_LICENSE("GPL");

dev_t devno;
struct cdev led_cdev;
struct class *led_cls;
struct device *led_devs;
static int led_open(struct inode *inode,struct file *filp)
{
	printk("led_open\n");
	return 0;
}

static int led_close(struct inode *inode,struct file *filp)
{
	printk("led_close\n");
	return 0;
}
static long led_ioctl(struct file *filp,unsigned int cmd,unsigned long arg)
{
	switch(cmd)
	{
	case LED2_ON:
	//	*gpx2dat = (*gpx2dat & ~(1 << 7)) | 1 << 7;
		writel((readl(gpx2dat) & ~(1 << 7)) | 1 << 7,gpx2dat);
		*gpx1dat = (*gpx1dat & ~(1 << 0));
		*gpf3dat = (*gpf3dat & ~(3 << 4));
		break;
	case LED2_OFF:
		*gpx2dat = (*gpx2dat & ~(1 << 7));
		*gpx1dat = (*gpx1dat & ~(1 << 0));
		*gpf3dat = (*gpf3dat & ~(3 << 4));
		break;
	case LED1_ON:
		*gpx2dat = (*gpx2dat & ~(1 << 7));
		*gpx1dat = (*gpx1dat & ~(1 << 0)) | 1 << 0;
		*gpf3dat = (*gpf3dat & ~(3 << 4));
		break;
	case LED1_OFF:
		*gpx2dat = (*gpx2dat & ~(1 << 7));
		*gpx1dat = (*gpx1dat & ~(1 << 0));
		*gpf3dat = (*gpf3dat & ~(3 << 4));
		break;
	case LED3_ON:
		*gpx2dat = (*gpx2dat & ~(1 << 7));
		*gpx1dat = (*gpx1dat & ~(1 << 0));
		*gpf3dat = (*gpf3dat & ~(1 << 4)) | 1 << 4;
		*gpf3dat = (*gpf3dat & ~(1 << 5));
		break;
	case LED3_OFF:
		*gpx2dat = (*gpx2dat & ~(1 << 7));
		*gpx1dat = (*gpx1dat & ~(1 << 0));
		*gpf3dat = (*gpf3dat & ~(3 << 4));
		break;
	case LED4_ON:
		*gpx2dat = (*gpx2dat & ~(1 << 7));
		*gpx1dat = (*gpx1dat & ~(1 << 0));
		*gpf3dat = (*gpf3dat & ~(1 << 4));
		*gpf3dat = (*gpf3dat & ~(1 << 5)) | 1 << 5;
		break;
	case LED4_OFF:
		*gpx2dat = (*gpx2dat & ~(1 << 7));
		*gpx1dat = (*gpx1dat & ~(1 << 0));
		*gpf3dat = (*gpf3dat & ~(3 << 4));
		break;
	}
	return 0;
}

struct file_operations led_ops = {
	.open = led_open,
	.unlocked_ioctl = led_ioctl,
	.release  = led_close,
};

int mypalt_drv_probe(struct platform_device *pdev)//一旦匹配成功,dev指针会被struct platform_device结构首地址赋值
{
	int ret;
	printk("match ok?\n");

	//封装字符设备框架
	devno = MKDEV(LED_MAJOR,LED_MINOR);

	ret = register_chrdev_region(devno,1,"led");

	cdev_init(&led_cdev,&led_ops);

	cdev_add(&led_cdev,devno,1);

	led_cls = class_create(THIS_MODULE,"led");
	
	led_devs = device_create(led_cls,NULL,devno,NULL,"led");

	gpx2con = ioremap(pdev->resource[0].start,4);
	gpx2dat = gpx2con + 1;

	gpx1con = ioremap(pdev->resource[1].start,4);
	gpx1dat = gpx1con + 1;

	gpf3con = ioremap(pdev->resource[2].start,4);
	gpf3dat = gpf3con + 1;

//	*gpx2con = (*gpx2con & ~(0xf << 28)) | 1 << 28;
	writel((readl(gpx2con) & ~(0xf << 28)) | 1 << 28,gpx2con);
	*gpx1con = (*gpx1con & ~(0xf << 0)) | 1 << 0;
	*gpf3con = (*gpf3con & ~(0xff << 16)) | 0x11 << 16;
	
	return 0;
}

int mypalt_drv_remove(struct platform_device *pdev)
{
	device_destroy(led_cls,devno);

	class_destroy(led_cls);

	cdev_del(&led_cdev);

	unregister_chrdev_region(devno,1);
	printk("remove success\n");
	return 0;
}

#if 0
struct platform_device_id id_table[] = {
	{
		.name = "abc",
	},
	{
		.name = "123",
	},
	{},
};
#endif

struct of_device_id fdt_com_table[] = {
	{
		.compatible = "17062drv,led",
	},
	{},
};

struct platform_driver pdrv = {
	.driver = {
		.name = "laowu",
		.of_match_table = fdt_com_table,
	},
	.probe = mypalt_drv_probe,
	.remove = mypalt_drv_remove,

//	.id_table = id_table, 
};

int plat_drv_init(void)
{
	platform_driver_register(&pdrv);
	printk("platform_driver init success\n");
	return 0;
}

module_init(plat_drv_init);

void plat_drv_exit(void)
{
	platform_driver_unregister(&pdrv);
	printk("platform_driver exit success\n");
	return;
}

module_exit(plat_drv_exit);

