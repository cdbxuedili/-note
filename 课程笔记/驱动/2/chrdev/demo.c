#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/slab.h>

//#define DEMO_MAJOR 500
//#define DEMO_MINOR 0

dev_t devno;
//struct cdev cdev;
struct cdev *cdev;
int demo_open(struct inode *inode,struct file *filp)
{
	printk("demo_open\n");
	return 0;
}

//struct file_operations fops;
//fops.open = demo_open;

struct file_operations fops = {
	.open = demo_open,
};

static int __init demo_init(void)
{
	int ret;
//	devno = MKDEV(DEMO_MAJOR,DEMO_MINOR);//静态申请
//	ret = register_chrdev_region(devno,1,"demo");//静态注册，容易造成设备好冲突;提高注册效率
	ret = alloc_chrdev_region(&devno,0,1,"demo");
	if(ret != 0)
	{
		printk("register_chrdev_region fail\n");
		return -1;
	}
	
	cdev = kzalloc(sizeof(struct cdev),GFP_KERNEL);
	if(cdev == NULL)
	{
		printk("kzalloc fail\n");
		return -1;
	}

//	cdev_init(&cdev,&fops);
//	cdev_add(&cdev,devno,1);
	
	cdev_init(cdev,&fops);
	cdev_add(cdev,devno,1);
	return 0;
}

static void __exit demo_exit(void)
{
//	cdev_del(&cdev);
	cdev_del(cdev);
	unregister_chrdev_region(devno,1);
	return;
}

module_init(demo_init);
module_exit(demo_exit);
MODULE_LICENSE("GPL");
