#include <linux/module.h>

MODULE_LICENSE("GPL");

int value;
module_param(value,int,0400);

static int __init demo_init(void)
{
	printk("18031 init\n");
	printk("value = %d\n",value);
	return 0;
}

module_init(demo_init);

static void __exit demo_exit(void)
{
	printk("18031 exit\n");
	return;
}
module_exit(demo_exit);
