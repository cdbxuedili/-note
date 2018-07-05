#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <asm/uaccess.h>
#include <linux/sched.h>

MODULE_LICENSE("GPL");

struct class *cls;
struct device *devs;

char kbuf[1024];

int demo_major;

wait_queue_head_t demo_rq;
wait_queue_head_t demo_wq;
int flag = 0;

int demo_open(struct inode *inode,struct file *filp)
{
	printk("open success\n");
	return 0;
}

ssize_t demo_read(struct file *filp,char __user *buf,size_t size,loff_t *off)
{
	int ret;
	ssize_t n;

	//阻塞
	wait_event(demo_rq,flag != 0);

	if(strlen(kbuf) + 1 > size)
		n = size;	
	else 
		n = strlen(kbuf) + 1;
	ret = copy_to_user(buf,kbuf,n);
	if(ret != 0)
	{
		printk("copy_to_user fail\n");
		return -EFAULT;
	}
	wake_up(&demo_wq);
	flag = 0;
	return n;
}
ssize_t demo_write(struct file *filp,const char __user *buf,size_t size,loff_t *off)
{
	int ret;
	
	ssize_t n;
	wait_event(demo_wq,flag == 0);
	if(size > sizeof(kbuf))
		n = sizeof(kbuf);
	else 
		n = size;
	ret = copy_from_user(kbuf,buf,n);
	if(ret != 0)
	{
		printk("copy_from_user fail\n");
		return -EFAULT;
	}

	wake_up(&demo_rq);
	flag = 1;
	printk("kernel:%s\n",kbuf);
	return n;
}

struct file_operations fops = {
	.owner = THIS_MODULE,
	.open = demo_open,
	.read = demo_read,
	.write = demo_write,
};

int demo_init(void)
{
	int err;
	demo_major = register_chrdev(0,"demo",&fops);
	if(demo_major == 0)
	{
		printk("register_chrdev\n");
		return -EFAULT;//将全局错误码转成虚拟地址
	}
	
	cls = class_create(THIS_MODULE,"demo");
	if(IS_ERR(cls))
	{
		printk("class_create fail\n");
		err = PTR_ERR(cls);
		goto err1;
	}

	devs = device_create(cls,NULL,MKDEV(demo_major,0),NULL,"demo");
	if(IS_ERR(devs))
	{
		err = PTR_ERR(devs);
		goto err2;
	}

	init_waitqueue_head(&demo_rq);
	init_waitqueue_head(&demo_wq);
	return 0;
err2:
	class_destroy(cls);
err1:
	unregister_chrdev(demo_major,"demo");
	return err;//本身已经是虚拟地址
}
module_init(demo_init);

void demo_exit(void)
{
	device_destroy(cls,MKDEV(demo_major,0));
	class_destroy(cls);
	unregister_chrdev(demo_major,"demo");
	return;
}
module_exit(demo_exit);
