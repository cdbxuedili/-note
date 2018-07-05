#include<linux/platform_device.h>
#include<linux/module.h>
#include<linux/init.h>
#include<linux/cdev.h>
#include<linux/fs.h>
#include<linux/device.h>
#include<asm/io.h>
#include<linux/sched.h>
#include<asm/uaccess.h>
#include<linux/interrupt.h>

#define ADC_MAJOR 500
#define ADC_MINOR 0

dev_t devno;

struct cdev fs4412_adc_cdev;

struct class *fs4412_adc_cls;
struct device *fs4412_adc_devs;

struct resource *res_mem;
struct resource *res_irq;

void *adc_base;//一定要定义为void *类型
wait_queue_head_t fs4412_adc_q;
int flag = 0;

int fs4412_adc_open(struct inode *inode,struct file *filp)
{
	printk("adc open done\n");
	return 0;
}

ssize_t fs4412_adc_read(struct file *filp,char __user *ubuf,size_t size,loff_t *off)
{
	int ret;
	int data;

	//ADCCON的第0位每次都需要重新设置为1
	writel(readl(adc_base) | 1,adc_base);

	wait_event(fs4412_adc_q,flag != 0);
	//从ADCDAT中获取数据
	data = readl(adc_base + 0x0C) & 0xfff;
	ret = copy_to_user(ubuf,&data,sizeof(data));
	flag = 0;
	return size;
}

irqreturn_t fs4412_adc_handler(int irqno,void *dev_id)
{
	//在中断使用后清除中断
	writel(0,adc_base + 0x18);

	flag = 1;
	wake_up(&fs4412_adc_q);
	return IRQ_HANDLED;
}

struct file_operations fs4412_adc_ops = {
	.open = fs4412_adc_open,
	.read = fs4412_adc_read,
};

int fs4412_adc_probe(struct platform_device *pdev)
{
	int ret;
	printk("adc match ok\n");

	devno = MKDEV(ADC_MAJOR,ADC_MINOR);
	
	ret = register_chrdev_region(devno,1,"adc");

	cdev_init(&fs4412_adc_cdev,&fs4412_adc_ops);
	cdev_add(&fs4412_adc_cdev,devno,1);

	fs4412_adc_cls = class_create(THIS_MODULE,"adc");

	fs4412_adc_devs = device_create(fs4412_adc_cls,NULL,devno,NULL,"myadc");

	//从设备树中获取寄存器基地址
	res_mem = platform_get_resource(pdev,IORESOURCE_MEM,0);
	adc_base = ioremap(res_mem->start,res_mem->end - res_mem->start);

	//操作ADCCON寄存器
	writel(1 << 16 | 1 << 14 | 0xff << 6,adc_base);

	//设置ADCMUX 为通道3
	writel(3,adc_base + 0x1C);

	//获取设备树中的中断号
	res_irq = platform_get_resource(pdev,IORESOURCE_IRQ,0);

	ret = request_irq(res_irq->start,fs4412_adc_handler,IRQF_DISABLED,"adc-int",NULL);

	init_waitqueue_head(&fs4412_adc_q);

	return 0;
}

int fs4412_adc_remove(struct platform_device *pdev)
{
	free_irq(res_irq->start,NULL);
	iounmap(adc_base);
	device_destroy(fs4412_adc_cls,devno);

	class_destroy(fs4412_adc_cls);
	cdev_del(&fs4412_adc_cdev);
	unregister_chrdev_region(devno,1);
	return 0;
}
struct of_device_id fs4412_adc_of_table[] = {
	{
		.compatible = "fs4412,adc",
	},
	{},
};

struct platform_driver fs4412_adc_drv = {
	.driver = {
		.name = "fs4412-adc",
		.of_match_table = fs4412_adc_of_table,
	},
	.probe = fs4412_adc_probe,
	.remove = fs4412_adc_remove,
};

module_platform_driver(fs4412_adc_drv);
MODULE_LICENSE("GPL");
