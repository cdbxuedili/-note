#include<linux/init.h>
#include<linux/module.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/slab.h>
#include<linux/device.h>

#define DEMO_MAJOR 500
#define DEMO_MINOR 0

MODULE_LICENSE("GPL");

struct cdev *cdev;
dev_t devno;

struct class *cls;
struct device *devs;

spinlock_t lock;

//int flag = 0;

int demo_open(struct inode *inode,struct file *filp)
{
	spin_lock(&lock);	
#if 0
	if(flag != 0)
	{
		spin_unlock(&lock);
		return -EAGAIN;
	}

	flag = 1;
#endif
	printk("demo_open\n");
	spin_unlock(&lock);
	return 0;
}

int demo_close(struct inode *inode,struct file *filp)
{
//	flag = 0;
	return 0;
}
struct file_operations ops = {
	.owner = THIS_MODULE,
	.open = demo_open,
	.release = demo_close,
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

	cdev_init(cdev,&ops);

	cdev_add(cdev,devno,1);

	cls = class_create(THIS_MODULE,"demo");

	devs = device_create(cls,NULL,devno,NULL,"demo");

	spin_lock_init(&lock);
	printk("demo_init\n");
	return 0;
}

module_init(demo_init);

static void demo_exit(void)
{
	device_destroy(cls,devno);
	class_destroy(cls);
	cdev_del(cdev);
	unregister_chrdev_region(devno,1);
	printk("demo_exit\n");
	return;
}
module_exit(demo_exit);
