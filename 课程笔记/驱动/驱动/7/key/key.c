#include<linux/platform_device.h>
#include<linux/init.h>
#include<linux/module.h>
#include<linux/cdev.h>
#include<linux/fs.h>
#include<linux/device.h>
#include<linux/sched.h>
#include<asm/uaccess.h>
#include<linux/interrupt.h>

#define KEY_MAJOR 501
#define KEY_MINOR 0

dev_t devno;
struct cdev fs4412_key_cdev;

struct class *fs4412_key_cls;
struct device *fs4412_key_devs;

struct resource *res_key1;
struct resource *res_key2;

int key;
int flag = 0;
wait_queue_head_t keyq;

int fs4412_key_open(struct inode *inode,struct file *filp)
{
	printk("key open done\n");
	return 0;
}

ssize_t fs4412_key_read(struct file *filp,char __user *ubuf,size_t size,loff_t *off)
{
	int ret;
	//如果按键没有按下，但是驱动执行到了copy_to_user位置，需要阻塞
	//阻塞,有中断产生时，让中断去唤醒当前阻塞位置
	wait_event_interruptible(keyq,flag != 0);
	ret = copy_to_user(ubuf,&key,size);
	if(ret != 0)
	{
		printk("copy_to_user error\n");
		return -EFAULT;
	}
	flag = 0;
	return size;
}

irqreturn_t fs4412_key_handler(int irqno,void *dev_id)
{
	if(irqno == res_key1->start)
		key = 1;

	if(irqno == res_key2->start)
		key = 2;

	flag = 1;
	wake_up_interruptible(&keyq);
/*
 * enum irqreturn
 * @IRQ_NONE		interrupt was not from this device
 * @IRQ_HANDLED		interrupt was handled by this device
 * @IRQ_WAKE_THREAD	handler requests to wake the handler thread
 enum irqreturn {
 	IRQ_NONE		= (0 << 0),
 	IRQ_HANDLED		= (1 << 0),
 	IRQ_WAKE_THREAD		= (1 << 1),
 };
 */

	return IRQ_HANDLED;

}

struct file_operations fs4412_key_ops = {
	.open = fs4412_key_open,
	.read = fs4412_key_read,
};

struct of_device_id fs4412_key_of_table[] = {
	{
		.compatible = "fs4412,key",
	},
	{},
};

int fs4412_key_probe(struct platform_device *pdev)
{
	int ret;
	printk("match ok!!!\n");
	devno = MKDEV(KEY_MAJOR,KEY_MINOR);

	ret = register_chrdev_region(devno,1,"key");

	cdev_init(&fs4412_key_cdev,&fs4412_key_ops);

	cdev_add(&fs4412_key_cdev,devno,1);

	fs4412_key_cls = class_create(THIS_MODULE,"key");

	fs4412_key_devs = device_create(fs4412_key_cls,NULL,devno,NULL,"key");

	res_key1 = platform_get_resource(pdev,IORESOURCE_IRQ,0);
	ret = request_irq(res_key1->start,fs4412_key_handler,IRQF_DISABLED | IRQF_TRIGGER_FALLING,"key1",NULL);

	res_key2 = platform_get_resource(pdev,IORESOURCE_IRQ,1);
	ret = request_irq(res_key2->start,fs4412_key_handler,IRQF_DISABLED | IRQF_TRIGGER_FALLING,"key2",NULL);

	init_waitqueue_head(&keyq);
	return 0;
}

int fs4412_key_remove(struct platform_device *pdev)
{
	device_destroy(fs4412_key_cls,devno);
	class_destroy(fs4412_key_cls);
	cdev_del(&fs4412_key_cdev);
	unregister_chrdev_region(devno,1);
	return 0;
}
struct platform_driver fs4412_key_drv = {
	.driver = {
		.name = "fs4412-key",
		.of_match_table = fs4412_key_of_table,
	},

	.probe = fs4412_key_probe,
	.remove = fs4412_key_remove,
};

module_platform_driver(fs4412_key_drv);
MODULE_LICENSE("GPL");
