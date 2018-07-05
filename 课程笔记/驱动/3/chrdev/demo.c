#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <asm/uaccess.h>

MODULE_LICENSE("GPL");

struct class *cls;
struct device *devs;

char krbuf[1024] = "I am from kernel";
char kwbuf[1024];

int demo_major;

int demo_open(struct inode *inode,struct file *filp)
{
	printk("open success\n");
	return 0;
}

ssize_t demo_read(struct file *filp,char __user *buf,size_t size,loff_t *off)
{
//	strncpy(buf,krbuf,strlen(krbuf) + 1);
//	return strlen(krbuf) + 1;
	
	int ret;
	ssize_t n;
	if(strlen(krbuf) + 1 > size)
		n = size;	
	else 
		n = strlen(krbuf) + 1;
	ret = copy_to_user(buf,krbuf,n);
	if(ret != 0)
	{
		printk("copy_to_user fail\n");
		return -EFAULT;
	}
	return n;
}
ssize_t demo_write(struct file *filp,const char __user *buf,size_t size,loff_t *off)
{
	int ret;
	
	ssize_t n;
	if(size > sizeof(kwbuf))
		n = sizeof(kwbuf);
	else 
		n = size;
	ret = copy_from_user(kwbuf,buf,n);
	if(ret != 0)
	{
		printk("copy_from_user fail\n");
		return -EFAULT;
	}
	printk("kernel:%s\n",kwbuf);
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
//	printk("major = %d\n",demo_major);
	
	cls = class_create(THIS_MODULE,"demo");
	if(IS_ERR(cls))
	{
		printk("class_create fail\n");
		err = PTR_ERR(cls);
		goto err1;
	}

#if 0
	if(cls == NULL)
	{
		printk("class_create fail\n");
		return -ENOMEM;
	}
#endif

	devs = device_create(cls,NULL,MKDEV(demo_major,0),NULL,"demo");
	if(IS_ERR(devs))
	{
		err = PTR_ERR(devs);
		goto err2;
	}
#if 0
	if(devs == NULL)
	{
		printk("device_create fail\n");
		return -ENOMEM;
	}
#endif
	return 0;
err2:
	class_destroy(cls);
err1:
	unregister_chrdev(demo_major,"demo");
	return err;//本身已经是虚拟地址
//err2: //这种方式也可以使用，但是有点麻烦
//	class_destroy(cls);
//	unregister_chrdev(demo_major,"demo");
//	return err;
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
