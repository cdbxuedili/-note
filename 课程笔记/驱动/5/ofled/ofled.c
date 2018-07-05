#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/gpio.h>
#include <linux/device.h>
#include <linux/of_gpio.h>

struct device_node *np;

int gpx2_7;
int gpx1_0;
int gpf3_4;
int gpf3_5;

int major;
struct class *cls;
struct device *devs;

int ofled_open(struct inode *inode,struct file *filp)
{
	gpio_set_value(gpx2_7,1);
	gpio_set_value(gpx1_0,1);
	gpio_set_value(gpf3_4,1);
	gpio_set_value(gpf3_5,1);
	return 0;
}

int ofled_close(struct inode *inode,struct file *filp)
{
	gpio_set_value(gpx2_7,0);
	gpio_set_value(gpx1_0,0);
	gpio_set_value(gpf3_4,0);
	gpio_set_value(gpf3_5,0);

	return 0;
}
struct file_operations fops = {
	.open = ofled_open,
	.release = ofled_close,
};

int demo_init(void)
{
	int ret;
	major = register_chrdev(0,"ofled",&fops);
	cls = class_create(THIS_MODULE,"ofled");
	devs = device_create(cls,NULL,MKDEV(major,0),NULL,"ofled");

	np = of_find_node_by_path("/ofled");

	gpx2_7 = of_get_named_gpio(np,"led2",0);
	gpx1_0 = of_get_named_gpio(np,"led1",0);
	gpf3_4 = of_get_named_gpio(np,"led3-4",0);
	gpf3_5 = of_get_named_gpio(np,"led3-4",1);

	ret = gpio_request(gpx2_7,NULL);
	if(ret != 0)
	{
		printk("gpio_request fali\n");
		return -EEXIST;
	}

	gpio_request(gpx1_0,NULL);
	gpio_request(gpf3_4,NULL);
	gpio_request(gpf3_5,NULL);

	gpio_direction_output(gpx2_7,1);
	gpio_direction_output(gpx1_0,1);
	gpio_direction_output(gpf3_4,1);
	gpio_direction_output(gpf3_5,1);
	return 0;
}
module_init(demo_init);

void demo_exit(void)
{
	return ;
}
module_exit(demo_exit);
MODULE_LICENSE("GPL");
