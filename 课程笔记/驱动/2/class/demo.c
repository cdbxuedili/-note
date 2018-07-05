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
	devno = MKDEV(DEMO_MAJOR,DEMO_MINOR);
	
	ret = register_chrdev_region(devno,1,"demo");

	cdev_init(&cdev,&fops);

	cdev_add(&cdev,devno,1);

	cls = class_create(THIS_MODULE,"18031demo");
	devs = device_create(cls,NULL,devno,NULL,"mydemo");

	return 0;
}
module_init(demo_init);

void demo_exit(void)
{
	device_destroy(cls,devno);
	class_destroy(cls);
	cdev_del(&cdev);
	unregister_chrdev_region(devno,1);
	return;
}	
module_exit(demo_exit);

MODULE_LICENSE("GPL");
