#include<linux/init.h>
#include<linux/module.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/slab.h>
#include<linux/device.h>

#include<asm/uaccess.h>
#include"head.h"

#define DEMO_MAJOR 251
#define DEMO_MINOR 0

MODULE_LICENSE("GPL");

struct cdev *cdev;
dev_t devno;

struct class *demo_cls;
struct device *demo_devs;
int count = 3;
int demo_major;

int demo_open(struct inode *inode,struct file *filp)
{
	printk("demo_open\n");
	return 0;
}

long demo_ioctl(struct file *filp,unsigned int cmd,unsigned long arg)
{
	int kval;
	int ktou_val = 101;
	int ret;
	switch(cmd)
	{
//	case 2:
//		printk("this our first cmd\n");
//		break;
	case DEMO_CMD1:
		printk("this our second cmd\n");
		break;
	case DEMO_CMD2:
//		kval = arg;
//		printk("recv from user kval = %d\n",kval);

//		kval = *(int *)arg;
//		printk("kval = %d\n",kval);
		ret = copy_from_user(&kval,(int *)arg,sizeof(kval));
		if(ret != 0)
		{
			printk("copy_from_user fail\n");
			return -EFAULT;
		}
		printk("kval = %d\n",kval);
		break;
	case DEMO_CMD3:
		ret = copy_to_user((void *)arg,&ktou_val,sizeof(ktou_val));
		if(ret != 0)
		{
			printk("copy_to_user fail\n");
			return -EFAULT;
		}

	}
	return 0;
}

struct file_operations ops = {
	.owner = THIS_MODULE,
	.open = demo_open,
	.unlocked_ioctl = demo_ioctl,
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
