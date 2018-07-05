#include <linux/init.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/input.h>
#include <linux/interrupt.h>
#include <linux/irqreturn.h>
#include <linux/sched.h>

struct input_dev *fs4412_idev;

struct resource *res_key2;
struct resource *res_key3;
struct timer_list t;
int glo_irqno;

int flag2 = 1,flag3 = 1;

irqreturn_t inputkey_handler(int irqno,void *id)
{
	glo_irqno = irqno;
	mod_timer(&t,jiffies + 30);
	return IRQ_HANDLED;
}

void inputkey_timer_handler(unsigned long data)
{
#if 0
	if(res_key2->start == glo_irqno)
	{
		//如果状态值为２则不关心按键的抬起状态
		input_event(fs4412_idev,EV_KEY,KEY_2,2);//设置了按键类型，以及按键值和按键状态，使用了唤醒机制	
		input_sync(fs4412_idev);//保证上面的工作一定被完成了
	}

	if(res_key3->start == glo_irqno)
	{
		input_event(fs4412_idev,EV_KEY,KEY_3,2);	
		input_sync(fs4412_idev);
	}
#endif

	if(res_key2->start == glo_irqno)
	{
		if(flag2 == 1)
		{
			input_event(fs4412_idev,EV_KEY,KEY_2,1);//设置了按键类型，以及按键值和按键状态，使用了唤醒机制	
			input_sync(fs4412_idev);//保证上面的工作一定被完成了
			flag2 = 0;
		}
		else if(flag2 == 0) 
		{
			input_event(fs4412_idev,EV_KEY,KEY_2,0);//设置了按键类型，以及按键值和按键状态，使用了唤醒机制	
			input_sync(fs4412_idev);//保证上面的工作一定被完成了
			flag2 = 1;
		}
	}

	if(res_key3->start == glo_irqno)
	{
		if(flag3 == 1)
		{
			input_event(fs4412_idev,EV_KEY,KEY_3,1);//设置了按键类型，以及按键值和按键状态，使用了唤醒机制	
			input_sync(fs4412_idev);//保证上面的工作一定被完成了
			flag3 = 0;
		}
		else if(flag3 == 0) 
		{
			input_event(fs4412_idev,EV_KEY,KEY_3,0);//设置了按键类型，以及按键值和按键状态，使用了唤醒机制	
			input_sync(fs4412_idev);//保证上面的工作一定被完成了
			flag3 = 1;
		}

	}
}

int inputkey_probe(struct platform_device *pdev)
{
	int ret;
	printk("match ok\n");
	
	fs4412_idev = input_allocate_device();
	
	set_bit(EV_KEY,fs4412_idev->evbit);
	set_bit(KEY_2,fs4412_idev->keybit);
	set_bit(KEY_3,fs4412_idev->keybit);

	res_key2 = platform_get_resource(pdev,IORESOURCE_IRQ,0);
	res_key3 = platform_get_resource(pdev,IORESOURCE_IRQ,1);

	ret = request_irq(res_key2->start,inputkey_handler,IRQF_TRIGGER_FALLING,"key2",NULL);
	ret = request_irq(res_key3->start,inputkey_handler,IRQF_TRIGGER_FALLING,"key3",NULL);

	init_timer(&t);
	t.function = inputkey_timer_handler;
	add_timer(&t);

	ret = input_register_device(fs4412_idev);
	return 0;
}

int inputkey_remove(struct platform_device *pdev)
{
	return 0;
}

struct of_device_id inputkey_match_tbl[] = {
	{
		.compatible = "fs4412,key",
	},
	{},
};

struct platform_driver pdrv = {
	.driver = {
		.name = "inputkey",
		.of_match_table = inputkey_match_tbl,
	},
	.probe = inputkey_probe,
	.remove = inputkey_remove,
};

module_platform_driver(pdrv);

MODULE_LICENSE("GPL");
