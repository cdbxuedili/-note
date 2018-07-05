#include<linux/init.h>
#include<linux/module.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/slab.h>
#include<linux/device.h>
#include<asm/uaccess.h>

#include<linux/of.h>
#include<linux/of_gpio.h>
#include<linux/gpio.h>

#include"led.h"

#define DEMO_MAJOR 251
#define DEMO_MINOR 0

MODULE_LICENSE("GPL");

struct cdev *cdev;
dev_t devno;

struct class *demo_cls;
struct device *demo_devs;
int count = 3;
int demo_major;

static struct device_node *mynp;
unsigned int gpx2_7;
unsigned int gpx1_0;
unsigned int gpf3_4;
unsigned int gpf3_5;

int demo_open(struct inode *inode,struct file *filp)
{
	int ret;

	gpx2_7 = of_get_named_gpio(mynp,"led2",0);
	if(gpx2_7 < 0)
	{
		printk("gpx2_7 error\n");
	}

	gpx1_0 = of_get_named_gpio(mynp,"led1",0);
	if(gpx1_0 < 0)
	{
		printk("gpx1_0 error\n");
	}

	gpf3_4 = of_get_named_gpio(mynp,"led3-4",0);
	if(gpf3_4 < 0)
	{
		printk("gpf3_4 error\n");
	}

	gpf3_5 = of_get_named_gpio(mynp,"led3-4",1);
	if(gpf3_5 < 0)
	{
		printk("gpf3_5 error\n");
	}

	ret = gpio_direction_output(gpx2_7,1);
	if(ret < 0)
	{
		printk("gpio_direction_output gpx2_7 error\n");
	}
	ret = gpio_direction_output(gpx1_0,1);
	if(ret < 0)
	{
		printk("gpio_direction_output gpx1_0 error\n");
	}

	ret = gpio_direction_output(gpf3_4,1);
	if(ret < 0)
	{
		printk("gpio_direction_output gpf3_4 error\n");
	}
	ret = gpio_direction_output(gpf3_5,1);
	if(ret < 0)
	{
		printk("gpio_direction_output gpf3_5 error\n");
	}

	//默认让灯关闭
	gpio_set_value(gpx2_7,0);
	gpio_set_value(gpx1_0,0);
	gpio_set_value(gpf3_4,0);
	gpio_set_value(gpf3_5,0);
	printk("demo_open\n");
	return 0;
}

int demo_close(struct inode *inode,struct file *filp)
{
	gpio_set_value(gpx2_7,0);
	gpio_set_value(gpx1_0,0);
	gpio_set_value(gpf3_4,0);
	gpio_set_value(gpf3_5,0);
	printk("demo_close\n");
	return 0;
}

long demo_ioctl(struct file *filp,unsigned int cmd,unsigned long arg)
{
	switch(cmd)
	{	
	case LED2_ON:
		gpio_set_value(gpx2_7,1);
		break;
	case LED2_OFF:
		gpio_set_value(gpx2_7,0);
		break;
	case LED1_ON:
		gpio_set_value(gpx1_0,1);
		break;
	case LED1_OFF:
		gpio_set_value(gpx1_0,0);
		break;
	case LED3_ON:
		gpio_set_value(gpf3_4,1);
		break;
	case LED3_OFF:
		gpio_set_value(gpf3_4,0);
		break;
	case LED4_ON:
		gpio_set_value(gpf3_5,1);
		break;
	case LED4_OFF:
		gpio_set_value(gpf3_5,0);
		break;
	}
	return 0;
}

struct file_operations ops = {
	.owner = THIS_MODULE,
	.open = demo_open,
	.unlocked_ioctl = demo_ioctl,
	.release = demo_close,
};


static int demo_init(void)
{
	int ret;
	int i;
	int x;
	devno = MKDEV(DEMO_MAJOR,DEMO_MINOR);

	ret = register_chrdev_region(devno,count,"17062");
	if(ret != 0)
	{
		printk("register_chrdev_region fail\n");
		ret = alloc_chrdev_region(&devno,0,count,"17062");
		if(ret != 0)
		{
			printk("alloc_chrdev_region fail\n");
			return -EFAULT;
		}
	}

	demo_major = MAJOR(devno);
	cdev = kzalloc(sizeof(struct cdev),GFP_KERNEL);
	if(IS_ERR(cdev) != 0)
	{
		ret = PTR_ERR(cdev);
		goto err1;
	}

	cdev_init(cdev,&ops);

	ret = cdev_add(cdev,devno,count);
	if(ret != 0)
	{
		printk("cdev_add fail\n");
		goto err2;
	}

	demo_cls = class_create(THIS_MODULE,"demo");
	if(IS_ERR(demo_cls) != 0)
	{
		ret = PTR_ERR(demo_cls);
		goto err3;
	}

	for(i = 0;i < count;i ++)
	{
		demo_devs = device_create(demo_cls,NULL,MKDEV(demo_major,i),NULL,"demo%d",i);
		if(IS_ERR(demo_devs))
		{
			ret = PTR_ERR(demo_devs);
			goto err4;
		}
	}
	
	mynp = of_find_node_by_path("/fsled");

	printk("demo_init\n");
	return 0;
err4:
	for(x = i - 1;x >= 0;x ++)
		device_destroy(demo_cls,MKDEV(demo_major,x));
	class_destroy(demo_cls);
err3:
	cdev_del(cdev);
err2:
	kfree(cdev);
err1:
	unregister_chrdev_region(devno,count);
	return ret;
	
}

module_init(demo_init);

static void demo_exit(void)
{
	int i;
	for(i = 0;i < count;i ++)
		device_destroy(demo_cls,MKDEV(demo_major,i));
	class_destroy(demo_cls);
	cdev_del(cdev);
	unregister_chrdev_region(devno,count);
	printk("demo_exit\n");
	return;
}
module_exit(demo_exit);
