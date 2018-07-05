#include<linux/init.h>
#include<linux/module.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/slab.h>
#include<linux/device.h>
#include<asm/uaccess.h>
#include<linux/wait.h>
#include<linux/sched.h>

#define DEMO_MAJOR 500
#define DEMO_MINOR 0

MODULE_LICENSE("GPL");

struct cdev *cdev;
dev_t devno;

struct class *cls;
struct device *devs;

wait_queue_head_t q;
char kbuf[1024];

int flag = 0;

int demo_open(struct inode *inode,struct file *filp)
{

	printk("demo_open\n");
	return 0;
}

ssize_t demo_read(struct file *filp,char __user *ubuf,size_t size,loff_t *off)
{
	int ret;

	//阻塞
//	wait_event(q,flag != 0);//因为条件不成立而阻塞
	wait_event_interruptible(q,flag != 0);
	ret = copy_to_user(ubuf,kbuf,size);
	if(ret != 0)
	{
		printk("copy_to_user error\n");
		return -EFAULT;
	}
	flag = 0;//防止多次调用读函数
	return size;
}

ssize_t demo_write(struct file *filp,const char __user *ubuf,size_t size,loff_t *off)
{
	int ret;

	if(size > sizeof(kbuf))
		size = sizeof(kbuf);

	ret = copy_from_user(kbuf,ubuf,size);
	if(ret != 0)
	{

	}

	//执行到这里说明kbuf中有数据了，所以应该去唤醒wait_event()
	wake_up(&q);
	flag = 1;
	return size;
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

	init_waitqueue_head(&q);//初始化等待队列头
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
