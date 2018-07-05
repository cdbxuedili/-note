#include<linux/init.h>
#include<linux/module.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/slab.h>
#include<linux/device.h>

#include<asm/uaccess.h>

#define DEMO_MAJOR 251
#define DEMO_MINOR 0

MODULE_LICENSE("GPL");

char kbuf[1024];
char krbuf[1024] = "hello farsight";
struct cdev *cdev;
dev_t devno;

struct class *demo_cls;
struct device *demo_devs;

int demo_open(struct inode *inode,struct file *filp)
{
	printk("demo_open\n");
	return 0;
}

ssize_t demo_write(struct file *filp,const char __user *ubuf,size_t size,loff_t *off)
{
	int ret;

	if(size > sizeof(kbuf))
		size = sizeof(kbuf);

	ret = copy_from_user(kbuf,ubuf,size);
	if(ret != 0)
	{
		printk("copy_from_user fail\n");
		return -EFAULT;
	}

	printk("recv data from user space:%s\n",kbuf);
	return size;
}


ssize_t demo_read(struct file *filp,char __user *ubuf,size_t size,loff_t *off)
{
	int ret;

	ret = copy_to_user(ubuf,krbuf,size);
	if(ret != 0)
	{
		return -EFAULT;
	}

	printk("read done\n");
	return size;

}

struct file_operations ops = {
	.owner = THIS_MODULE,
	.open = demo_open,
	.write = demo_write,
	.read = demo_read,
};


static int demo_init(void)
{
	int ret;

	devno = MKDEV(DEMO_MAJOR,DEMO_MINOR);

	ret = register_chrdev_region(devno,1,"17062");
	if(ret != 0)
	{
		printk("register_chrdev_region fail\n");
		ret = alloc_chrdev_region(&devno,0,1,"17062");
		if(ret != 0)
		{
			printk("alloc_chrdev_region fail\n");
			return -EFAULT;
		}
	}
	cdev = kzalloc(sizeof(struct cdev),GFP_KERNEL);
	if(IS_ERR(cdev) != 0)
	{
		ret = PTR_ERR(cdev);
		goto err1;
	}

	cdev_init(cdev,&ops);

	ret = cdev_add(cdev,devno,1);
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

	demo_devs = device_create(demo_cls,NULL,devno,NULL,"demo");
	if(IS_ERR(demo_devs))
	{
		ret = PTR_ERR(demo_devs);
		goto err4;
	}

	printk("demo_init\n");
	return 0;
err4:
	class_destroy(demo_cls);
err3:
	cdev_del(cdev);
err2:
	kfree(cdev);
err1:
	unregister_chrdev_region(devno,1);
	return ret;
	
}

module_init(demo_init);

static void demo_exit(void)
{
	device_destroy(demo_cls,devno);
	class_destroy(demo_cls);
	cdev_del(cdev);
	unregister_chrdev_region(devno,1);
	printk("demo_exit\n");
	return;
}
module_exit(demo_exit);
