#include <linux/init.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/irqreturn.h>
#include <linux/interrupt.h>
#include <asm/io.h>
#include <linux/sched.h>
#include <asm/uaccess.h>

int major;
struct class *cls;
struct device *devs;

void __iomem *adc_base;
struct resource *res_mem;
struct resource *res_irq;

int flag;
wait_queue_head_t adc_q;

irqreturn_t fs4412_adc_handler(int irqno,void *id)
{
	//清除中断
	writel(0,adc_base + 0x18);
	wake_up(&adc_q);
	flag = 1;
	return IRQ_HANDLED;
}

struct of_device_id fs4412_adc_match_tbl[] = {
	{
		.compatible = "fs4412,adc",
	},
	{},
};

int fs4412_adc_open(struct inode *inode,struct file *filp)
{
	return 0;
}

ssize_t fs4412_adc_read(struct file *filp,char __user *ubuf,size_t size,loff_t *off)
{
	int ret;
	unsigned int data;

	//开始转换,会产生中断
	writel(readl(adc_base) | 1,adc_base);

	wait_event(adc_q,flag != 0);
	data = readl(adc_base + 0x0c) & 0xfff;
	ret = copy_to_user(ubuf,&data,sizeof(data));

	flag = 0;
	return sizeof(data);
}

struct file_operations fops = {
	.owner = THIS_MODULE,
	.open = fs4412_adc_open,
	.read = fs4412_adc_read,
};

int fs4412_adc_probe(struct platform_device *pdev)
{
	int ret;
	printk("match ok\n");

	major = register_chrdev(0,"adc",&fops);
	cls = class_create(THIS_MODULE,"adc");
	devs = device_create(cls,NULL,MKDEV(major,0),NULL,"adc");

	res_mem = platform_get_resource(pdev,IORESOURCE_MEM,0);
	adc_base = ioremap(res_mem->start,0x20);
	
	//设置了预分频值　使能了预分频值　　设置了转换精度
	writel(255 << 6 | 1 << 14 | 1 << 16,adc_base);

	//设置转换通道
	writel(3,adc_base + 0x1c);

	res_irq = platform_get_resource(pdev,IORESOURCE_IRQ,0);
	ret = request_irq(res_irq->start,fs4412_adc_handler,IRQF_DISABLED,"adc",NULL);

	init_waitqueue_head(&adc_q);
	return 0;
}

int fs4412_adc_remove(struct platform_device *pdev)
{
	free_irq(res_irq->start,NULL);
	device_destroy(cls,MKDEV(major,0));
	class_destroy(cls);
	unregister_chrdev(major,"adc");
	return 0;
}
struct platform_driver fs4412_adc_pdrv = {
	.driver = {
		.name = "fs4412-adc",
		.of_match_table = fs4412_adc_match_tbl,
	},
	.probe = fs4412_adc_probe,
	.remove = fs4412_adc_remove,
};

module_platform_driver(fs4412_adc_pdrv);
MODULE_LICENSE("GPL");
