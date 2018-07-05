#include<linux/init.h>
#include<linux/module.h>
#include<linux/platform_device.h>
#include<linux/sched.h>
#include<linux/interrupt.h>
#include<linux/input.h>
#include<linux/timer.h>
#include<asm/io.h>

#define GPX1DAT 0x11000c24

unsigned int *gpx1dat;

struct input_dev *input_dev;

struct resource *res_key1;
struct resource *res_key2;

struct timer_list keytimer;
int glo_irqno;
irqreturn_t inputkey_handler(int irqno,void *dev_id)
{
	glo_irqno = irqno;
	mod_timer(&keytimer,jiffies + 50);
	return IRQ_HANDLED;
}

void keytimer_handler(unsigned long data)
{
	int value1,value2;

	value1 = readl(gpx1dat);
	value2 = readl(gpx1dat);
	if(glo_irqno == res_key1->start)
	{
		input_event(input_dev,EV_KEY,KEY_1,!!value1);//按下	
		input_sync(input_dev);//为了保证每次数据传递完整
	}
	else 
	{
		input_event(input_dev,EV_KEY,KEY_1,!value1);//松开
		input_sync(input_dev);//为了保证每次数据传递完整
	}

	if(glo_irqno == res_key2->start)
	{
		input_event(input_dev,EV_KEY,KEY_2,!!value2);//按下	
		input_sync(input_dev);//为了保证每次数据传递完整
	}
	else 
	{
		input_event(input_dev,EV_KEY,KEY_2,!value2);//松开
		input_sync(input_dev);//为了保证每次数据传递完整
	}

}

int fs4412_inputkey_probe(struct platform_device *pdev)
{
	int ret;
	printk("match ok\n");
	input_dev = input_allocate_device();
	
	set_bit(EV_KEY,input_dev->evbit);//指定事件类型
	set_bit(KEY_1,input_dev->keybit);//指定具体在当前事件中使用的按键值
	set_bit(KEY_2,input_dev->keybit);

	res_key1 = platform_get_resource(pdev,IORESOURCE_IRQ,0);
	ret = request_irq(res_key1->start,inputkey_handler,IRQF_DISABLED | IRQF_TRIGGER_FALLING,"key1",NULL);

	res_key2 = platform_get_resource(pdev,IORESOURCE_IRQ,1);
	ret = request_irq(res_key2->start,inputkey_handler,IRQF_DISABLED | IRQF_TRIGGER_FALLING,"key2",NULL);

	gpx1dat = ioremap(GPX1DAT,0x4);

	init_timer(&keytimer);
	keytimer.function = keytimer_handler;
	add_timer(&keytimer);
	ret = input_register_device(input_dev);
	return 0;
}

int fs4412_inputkey_remove(struct platform_device *pdev)
{
	input_unregister_device(input_dev);
	del_timer(&keytimer);
	iounmap(gpx1dat);
	free_irq(res_key2->start);
	
	return 0;
}
struct of_device_id fs4412_inputkey_of_table[] = {
	{
		.compatible = "fs4412,key",
	},
	{},
};

struct platform_driver fs4412_inputkey_drv = {
	.driver = {
		.name = "inputkey",
		.of_match_table = fs4412_inputkey_of_table,
	},
	.probe = fs4412_inputkey_probe,
	.remove = fs4412_inputkey_remove,
};

int fs4412_inputkey_init(void)
{
	platform_driver_register(&fs4412_inputkey_drv);
	printk("fs4412_inputkey_init success\n");
	return 0;
}
module_init(fs4412_inputkey_init);

void fs4412_inputkey_exit(void)
{
	platform_driver_unregister(&fs4412_inputkey_drv);
	return ;
}
module_exit(fs4412_inputkey_exit);

MODULE_LICENSE("GPL");
