#include<linux/init.h>
#include<linux/module.h>
#include<linux/irqreturn.h>
#include<linux/interrupt.h>
#include<linux/input.h>
#include<linux/gpio.h>
#include<linux/of.h>
#include<linux/of_gpio.h>

struct input_dev *fs4412_dev;
struct device_node *np;


int gpx1_1;
int gpx1_2;
int gpx3_2;

int irqno1,irqno2,irqno3;

irqreturn_t fs4412_key_handler(int irqno,void *id)
{
	if(irqno == irqno1)
	{
		input_event(fs4412_dev,EV_KEY,KEY_1,2);
		input_sync(fs4412_dev);
	}
	if(irqno == irqno2)
	{
		input_event(fs4412_dev,EV_KEY,KEY_2,2);
		input_sync(fs4412_dev);
	}
	if(irqno == irqno3)
	{
		input_event(fs4412_dev,EV_KEY,KEY_3,2);
		input_sync(fs4412_dev);
	}
	return IRQ_HANDLED;
}

int fs4412_key_init(void)
{
	int ret;
	fs4412_dev = input_allocate_device();
	
	set_bit(EV_KEY,fs4412_dev->evbit);
	set_bit(KEY_1,fs4412_dev->keybit);
	set_bit(KEY_2,fs4412_dev->keybit);
	set_bit(KEY_3,fs4412_dev->keybit);

	//查找设备树节点
	np = of_find_node_by_path("/fskey");
	
	//获取引脚编号
	gpx1_1 = of_get_named_gpio(np,"key1",0);
	gpx1_2 = of_get_named_gpio(np,"key2",0);
	gpx3_2 = of_get_named_gpio(np,"key3",0);

	//注册引脚编号
	gpio_request(gpx1_1,NULL);
	gpio_request(gpx1_2,NULL);
	gpio_request(gpx3_2,NULL);

	//设置引脚为输入模式
	gpio_direction_input(gpx1_1);
	gpio_direction_input(gpx1_2);
	gpio_direction_input(gpx3_2);
	
	//获取虚拟中断号
	irqno1 = gpio_to_irq(gpx1_1);
	irqno2 = gpio_to_irq(gpx1_2);
	irqno3 = gpio_to_irq(gpx3_2);

	//注册中断
	ret = request_irq(irqno1,fs4412_key_handler,IRQF_DISABLED | IRQF_TRIGGER_FALLING,"key1",NULL);
	ret = request_irq(irqno2,fs4412_key_handler,IRQF_DISABLED | IRQF_TRIGGER_FALLING,"key2",NULL);
	ret = request_irq(irqno3,fs4412_key_handler,IRQF_DISABLED | IRQF_TRIGGER_FALLING,"key3",NULL);
	ret = input_register_device(fs4412_dev);
	return 0;
}

module_init(fs4412_key_init);

void fs4412_key_exit(void)
{
	return;
}
module_exit(fs4412_key_exit);

MODULE_LICENSE("GPL");
