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

struct timer_list keytimer;
int glo_irqno;

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
	glo_irqno = irqno;
	mod_timer(&keytimer,jiffies + 5 * HZ / 100);//设置定时时间	
	return IRQ_HANDLED;

}

void fs4412_key_timer_handler(unsigned long data)
{
	if(res_key1->start == glo_irqno)
		key = 1;

	if(res_key2->start == glo_irqno)
		key = 2;

	flag = 1;
	wake_up_interruptible(&keyq);
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

	init_timer(&keytimer);
	keytimer.function = fs4412_key_timer_handler;//当定时器时间到达时执行这个中断函数
	add_timer(&keytimer);//将定时及注册进内核
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
