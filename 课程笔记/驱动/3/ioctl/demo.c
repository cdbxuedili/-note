#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <asm/uaccess.h>
#include "head.h"

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

long demo_ioctl(struct file *filp,unsigned int cmd,unsigned long arg)
{
	int ret;
	struct test t = {
		.a = 111,
		.b = 'w',
	};
	switch(cmd)
	{
#if 0
	case 1:
		printk("ioctl cmd1\n");
		break;
	case 2:
		printk("ioctl cmd2\n");
		break;
#endif
	case TEST_CMD1:
		printk("ioctl cmd1\n");
		break;
	case TEST_CMD2:
		printk("ioctl cmd2\n");
		break;
	case TEST_CMD3:
		printk("%ld\n",arg);
		break;
	case TEST_CMD4:
		printk("%d\n",*(unsigned int *)arg);
		break;
	case TEST_CMD5:
		ret = copy_to_user((void *)arg,&t,sizeof(t));
		if(ret != 0)
		{
			return -EFAULT;
		}
		break;
	}

	return 0;
}

struct file_operations fops = {
	.owner = THIS_MODULE, 
	.open = demo_open,
	.unlocked_ioctl = demo_ioctl,
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
