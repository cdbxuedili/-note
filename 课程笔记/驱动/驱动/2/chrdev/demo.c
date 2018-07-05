#include<linux/init.h>
#include<linux/module.h>
#include<linux/fs.h>
#include<linux/cdev.h>

#define DEMO_MAJOR 500
#define DEMO_MINOR 0

MODULE_LICENSE("GPL");

struct cdev cdev;
dev_t devno;

int demo_open(struct inode *inode,struct file *filp)
{
	printk("demo_open\n");
	return 0;
}

#if 0
struct file_operations ops;
ops.owner = THIS_MODULE;
ops.open = demo_open;
#endif
struct file_operations ops = {
	.owner = THIS_MODULE,
	.open = demo_open,
};


static int demo_init(void)
{
	int ret;

	devno = MKDEV(DEMO_MAJOR,DEMO_MINOR);

	ret = register_chrdev_region(devno,1,"17062");

	cdev_init(&cdev,&ops);

	cdev_add(&cdev,devno,1);
	printk("demo_init\n");
	return 0;
}

module_init(demo_init);

static void demo_exit(void)
{
	cdev_del(&cdev);
	unregister_chrdev_region(devno,1);
	printk("demo_exit\n");
	return;
}
module_exit(demo_exit);
