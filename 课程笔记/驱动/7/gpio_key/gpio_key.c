#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#include <linux/device.h>
#include <linux/sched.h>
#include <linux/irqreturn.h>
#include <linux/interrupt.h>
#include <linux/of.h>
#include <linux/of_gpio.h>

int major;

struct class *cls;
struct device *devs;
struct device_node *np;

int key1;
int key2;
int key3;

int irqno1;
int irqno2;
int irqno3;

int kvalue;

wait_queue_head_t fs4412_gpiokey_q;
int flag = 0;

irqreturn_t fs4412_gpiokey_handler(int irqno,void *id)
{
	if(irqno == irqno1)
		kvalue = 2;

	if(irqno == irqno2)
		kvalue = 3;

	if(irqno == irqno3)
		kvalue = 4;

	wake_up(&fs4412_gpiokey_q);
	flag = 1;
	return IRQ_HANDLED;
}

int fs4412_gpiokey_open(struct inode *inode,struct file *filp)
{
	return 0;
}

ssize_t fs4412_gpiokey_read(struct file *filp,char __user *ubuf,size_t size,loff_t *off)
{
	int ret;
	
	wait_event(fs4412_gpiokey_q,flag != 0);
	ret = copy_to_user(ubuf,&kvalue,sizeof(kvalue));
	
	flag = 0;
	return sizeof(kvalue);
}

struct file_operations fops = {
	.owner = THIS_MODULE,
	.open = fs4412_gpiokey_open,
	.read = fs4412_gpiokey_read,
};

int fs4412_gpiokey_init(void)
{
	int ret;
	major = register_chrdev(0,"key",&fops);
	cls = class_create(THIS_MODULE,"key");
	devs = device_create(cls,NULL,MKDEV(major,0),NULL,"key");

	//获取设备树中fskey节点的结构体首地址
	np = of_find_node_by_path("/fskey");

	//获取某个属性的对应引脚编号
	key1 = of_get_named_gpio(np,"key1",0);
	key2 = of_get_named_gpio(np,"key2",0);
	key3 = of_get_named_gpio(np,"key3",0);

	//注册引脚编号到内核中
	gpio_request(key1,NULL);
	gpio_request(key2,NULL);
	gpio_request(key3,NULL);

	//设置引脚为输入模式
	gpio_direction_input(key1);
	gpio_direction_input(key2);
	gpio_direction_input(key3);
	
	//获取虚拟中断号
	irqno1 = gpio_to_irq(key1);	
	irqno2 = gpio_to_irq(key2);	
	irqno3 = gpio_to_irq(key3);	

	//注册中断
	ret = request_irq(irqno1,fs4412_gpiokey_handler,IRQF_TRIGGER_FALLING,"key1",NULL);
	ret = request_irq(irqno2,fs4412_gpiokey_handler,IRQF_TRIGGER_FALLING,"key2",NULL);
	ret = request_irq(irqno3,fs4412_gpiokey_handler,IRQF_TRIGGER_FALLING,"key3",NULL);

	init_waitqueue_head(&fs4412_gpiokey_q);
	return 0;
}
module_init(fs4412_gpiokey_init);

void fs4412_gpiokey_exit(void)
{
	return ;
}
module_exit(fs4412_gpiokey_exit);
MODULE_LICENSE("GPL");
