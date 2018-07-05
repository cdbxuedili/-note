#include<linux/init.h>
#include<linux/module.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/slab.h>
#include<linux/device.h>
#include<asm/uaccess.h>
#include<linux/wait.h>
#include<linux/sched.h>
#include<linux/poll.h>

#define DEMO_MAJOR 500
#define DEMO_MINOR 0

MODULE_LICENSE("GPL");

struct cdev *cdev;
dev_t devno;

struct class *cls;
struct device *devs;

char kbuf[1024];

wait_queue_head_t readq;
wait_queue_head_t writeq;

int flag = 0;

int demo_open(struct inode *inode,struct file *filp)
{

	printk("demo_open\n");
	return 0;
}

ssize_t demo_read(struct file *filp,char __user *ubuf,size_t size,loff_t *off)
{
	int ret;
	
	wait_event(readq,flag != 0);
	ret = copy_to_user(ubuf,kbuf,size);
	if(ret != 0)
	{
		printk("copy_to_user error\n");
		return -EFAULT;
	}
	
	flag = 0;
	wake_up(&writeq);

	return size;
}

ssize_t demo_write(struct file *filp,const char __user *ubuf,size_t size,loff_t *off)
{
	int ret;
	
	wait_event(writeq,flag == 0);
	if(size > sizeof(kbuf))
		size = sizeof(kbuf);

	ret = copy_from_user(kbuf,ubuf,size);
	if(ret != 0)
	{

	}

	flag = 1;
	wake_up(&readq);

	return size;
}

unsigned int demo_poll(struct file *filp,struct poll_table_struct *p)
{
	int mask = 0;
	poll_wait(filp,&readq,p);
	poll_wait(filp,&writeq,p);

	if(flag == 0)//需要写数据
		mask |= POLLOUT;
	else 
		mask |= POLLIN;

	return mask;
}

int demo_close(struct inode *inode,struct file *filp)
{
	return 0;
}
struct file_operations ops = {
	.owner = THIS_MODULE,
	.open = demo_open,

	.read = demo_read,
	.write = demo_write,
	.poll = demo_poll,

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

	init_waitqueue_head(&readq);
	init_waitqueue_head(&writeq);
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
