#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <asm/uaccess.h>

MODULE_LICENSE("GPL");

struct class *cls;
struct device *devs;

int demo_major;

atomic_t v;

int demo_open(struct inode *inode,struct file *filp)
{
	
	if(!atomic_dec_and_test(&v))
	{
		atomic_inc(&v);
		return -EFAULT;
	}
	return 0;
}
int demo_close(struct inode *inode,struct file *filp)
{
	atomic_inc(&v);
	printk("open success\n");
	return 0;
}


struct file_operations fops = {
	.owner = THIS_MODULE,
	.open = demo_open,
	.release = demo_close,
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

	devs = device_create(cls,NULL,MKDEV(demo_major,0),NULL,"demo");
	if(IS_ERR(devs))
	{
		err = PTR_ERR(devs);
		goto err2;
	}

	atomic_set(&v,1);

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
