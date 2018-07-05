#include<linux/init.h>
#include<linux/module.h>
#include<linux/interrupt.h>
#include<linux/gpio.h>
#include<linux/of.h>
#include<linux/of_gpio.h>
#include<linux/input.h>

struct input_dev *input_dev;
struct device_node *np;

unsigned int gpx1_1;
unsigned int gpx1_2;
unsigned int gpx3_2;

int irq1,irq2,irq3;
struct timer_list timer;
int glo_irqno;

irqreturn_t demo_handler(int irqno,void *dev_id)
{
	glo_irqno = irqno;
	mod_timer(&timer,jiffies + 50);
	
	return IRQ_HANDLED;
}

void timer_handler(unsigned long data)
{
	int value1,value2,value3;
	value1 = gpio_get_value(gpx1_1);
	if(glo_irqno == irq1)
	{
		input_event(input_dev,EV_KEY,KEY_1,!!value1);
		input_sync(input_dev);
	}
	else 
	{
		input_event(input_dev,EV_KEY,KEY_1,!value1);
		input_sync(input_dev);
	}

	value2 = gpio_get_value(gpx1_2);
	if(glo_irqno == irq2)
	{
		input_event(input_dev,EV_KEY,KEY_2,!!value2);
		input_sync(input_dev);
	}
	else 
	{
		input_event(input_dev,EV_KEY,KEY_2,!value2);
		input_sync(input_dev);
	}

	value3 = gpio_get_value(gpx3_2);
	if(glo_irqno == irq3)
	{
		input_event(input_dev,EV_KEY,KEY_3,!!value3);
		input_sync(input_dev);
	}
	else 
	{
		input_event(input_dev,EV_KEY,KEY_3,!value3);
		input_sync(input_dev);
	}
}

int demo_init(void)
{
	int ret;
	input_dev = input_allocate_device();

	set_bit(EV_KEY,input_dev->evbit);
	set_bit(KEY_1,input_dev->keybit);
	set_bit(KEY_2,input_dev->keybit);
	set_bit(KEY_3,input_dev->keybit);

	np = of_find_node_by_path("/fskey");//通过路径寻找设备树节点

	//获取gpio引脚编号
	gpx1_1 = of_get_named_gpio(np,"key1",0);
	if(gpx1_1 < 0)
	{
		printk("of_get_named_gpio gpx1_1 error\n");
	}

	gpx1_2 = of_get_named_gpio(np,"key2",0);
	if(gpx1_2 < 0)
	{
		printk("of_get_named_gpio gpx1_2 error\n");
	}

	gpx3_2 = of_get_named_gpio(np,"key3",0);
	if(gpx3_2 < 0)
	{
		printk("of_get_named_gpio gpx3_2 error\n");
	}

	ret = gpio_request(gpx1_1,NULL);
	if(ret < 0)
	{
		printk("ret = %d\n",ret);
	}
	ret = gpio_request(gpx1_2,NULL);
	ret = gpio_request(gpx3_2,NULL);

	//设置引脚为输入引脚
	gpio_direction_input(gpx1_1);
	gpio_direction_input(gpx1_2);
	gpio_direction_input(gpx3_2);

	//获取中断号
	irq1 = gpio_to_irq(gpx1_1);
	irq2 = gpio_to_irq(gpx1_2);
	irq3 = gpio_to_irq(gpx3_2);

	//注册中断
	ret = request_irq(irq1,demo_handler,IRQF_DISABLED | IRQF_TRIGGER_FALLING,"key1",NULL);
	ret = request_irq(irq2,demo_handler,IRQF_DISABLED | IRQF_TRIGGER_FALLING,"key2",NULL);
	ret = request_irq(irq3,demo_handler,IRQF_DISABLED | IRQF_TRIGGER_FALLING,"key3",NULL);

	init_timer(&timer);
	timer.function = timer_handler;
	add_timer(&timer);

	ret = input_register_device(input_dev);
	printk("demo_init\n");
	return 0;
}
module_init(demo_init);

void demo_exit(void)
{
	printk("demo_exit\n");

}
module_exit(demo_exit);

MODULE_LICENSE("GPL");
