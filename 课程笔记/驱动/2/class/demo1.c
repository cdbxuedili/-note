#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>

#define DEMO_MAJOR 600
#define DEMO_MINOR 0

dev_t devno;
struct cdev cdev;
struct class *cls;
struct device *devs;

int demo_open(struct inode *inode,struct file *filp)
{
	printk("demo_open\n");
	return 0;
}

struct file_operations fops = {
	.open = demo_open,	
};
int demo_init(void)
{
	int ret;
	int i;
	devno = MKDEV(DEMO_MAJOR,DEMO_MINOR);
	
	ret = register_chrdev_region(devno,3,"demo");

	cdev_init(&cdev,&fops);

	cdev_add(&cdev,devno,3);

	cls = class_create(THIS_MODULE,"18031demo");
//	devs = device_create(cls,NULL,devno,NULL,"mydemo");
	for(i = 0;i < 3;i ++)
	{
		devs = device_create(cls,NULL,MKDEV(DEMO_MAJOR,i),NULL,"mydemo%d",i);
	}

	return 0;
}
module_init(demo_init);

void demo_exit(void)
{
	int i;
//	device_destroy(cls,devno);
	
	for(i = 2;i >= 0;i --)
		device_destroy(cls,MKDEV(DEMO_MAJOR,i));
	class_destroy(cls);
	cdev_del(&cdev);
	unregister_chrdev_region(devno,3);
	return;
}	
module_exit(demo_exit);

MODULE_LICENSE("GPL");
