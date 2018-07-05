#include<linux/init.h>
#include<linux/module.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/slab.h>
#include<linux/device.h>
#include<linux/poll.h>
#include<linux/sched.h>

#include<asm/uaccess.h>

#define DEMO_MAJOR 251
#define DEMO_MINOR 0

MODULE_LICENSE("GPL");

struct cdev *cdev;
dev_t devno;

struct class *demo_cls;
struct device *demo_devs;
int count = 3;
int demo_major;

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

	}
	flag = 0;
	wake_up(&writeq);
	return size;
}

ssize_t demo_write(struct file *filp,const char __user *ubuf,size_t size,loff_t *off)
{
	int ret;

	if(size > sizeof(kbuf))
		size = sizeof(kbuf);
	wait_event(writeq,flag == 0);
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

	if(flag == 0)
		mask |= POLLOUT;
	else 
		mask |= POLLIN;

	return mask;
}

int demo_close(struct inode *inode,struct file *filp)
{
	printk("demo_close\n");
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

	init_waitqueue_head(&readq);
	init_waitqueue_head(&writeq);

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
