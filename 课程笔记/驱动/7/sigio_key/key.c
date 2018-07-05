#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/platform_device.h>
#include <linux/device.h>
#include <linux/sched.h>
#include <linux/irqreturn.h>
#include <asm/uaccess.h>
#include <linux/interrupt.h>
#include <linux/poll.h>

int major;

struct class *cls;
struct device *devs;

struct resource *res_key2;
struct resource *res_key3;

int kvalue;
int flag = 0;
struct timer_list t;
int glo_irqno;

struct tasklet_struct ts;
struct fasync_struct *fa;

irqreturn_t fs4412_key_handler(int irqno,void *id)//就是上半部
{
	glo_irqno = irqno;
	mod_timer(&t,jiffies + 30);
	return IRQ_HANDLED;
}


void fs4412_key_timer_handler(unsigned long data)
{
	if(glo_irqno == res_key2->start)
		kvalue = 2;		

	if(glo_irqno == res_key3->start)
		kvalue = 3;
	
	kill_fasync(&fa,SIGIO,POLLIN);//给进程注册SIGIO信号
	
}

int fs4412_key_open(struct inode *inode,struct file *filp)
{
	return 0;
}

ssize_t fs4412_key_read(struct file *filp,char __user *ubuf,size_t size,loff_t *off)
{
	int ret;
	
	ret = copy_to_user(ubuf,&kvalue,sizeof(kvalue));
	if(ret != 0)
	{
		return -EFAULT;
	}
	return sizeof(kvalue);
}

//参数３是一个逻辑值
int fs4412_key_fasync(int fd,struct file *filp,int on)
{
	return fasync_helper(fd,filp,on,&fa);	
}

struct file_operations fops = {
	.owner = THIS_MODULE,
	.open = fs4412_key_open,
	.read = fs4412_key_read,
	.fasync = fs4412_key_fasync,
};

int fs4412_key_probe(struct platform_device *pdev)
{
	int ret;
	printk("match ok\n");

	major = register_chrdev(0,"key",&fops);
	cls = class_create(THIS_MODULE,"key");
	devs = device_create(cls,NULL,MKDEV(major,0),NULL,"key");

	res_key2 = platform_get_resource(pdev,IORESOURCE_IRQ,0);	
	res_key3 = platform_get_resource(pdev,IORESOURCE_IRQ,1);	

	//注册中断处理函数
	ret = request_irq(res_key2->start,fs4412_key_handler,IRQF_TRIGGER_FALLING,"key2",NULL);
	ret = request_irq(res_key3->start,fs4412_key_handler,IRQF_TRIGGER_FALLING,"key3",NULL);

	init_timer(&t);
	t.function = fs4412_key_timer_handler;
	add_timer(&t);

	return 0;
}

int fs4412_key_remove(struct platform_device *pdev)
{
	free_irq(res_key3->start,NULL);
	free_irq(res_key2->start,NULL);
	device_destroy(cls,MKDEV(major,0));
	class_destroy(cls);
	unregister_chrdev(major,"key");
	return 0;
}
struct of_device_id fs4412_key_mytbl[] = {
	{
		.compatible = "fs4412,key",
	},
	{},
};

struct platform_driver fs4412_key_pdrv = {
	.driver = {
		.name = "fs4412-key",
		.of_match_table = fs4412_key_mytbl,
	},

	.probe = fs4412_key_probe,
	.remove = fs4412_key_remove,
};

module_platform_driver(fs4412_key_pdrv);

MODULE_LICENSE("GPL");
