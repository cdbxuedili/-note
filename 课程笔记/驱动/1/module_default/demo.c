#include <linux/module.h>
MODULE_LICENSE("GPL");

int init_module(void)
{
	printk("18031 init\n");
	return 0;
}

void cleanup_module(void)
{
	printk("18031 exit\n");
	return;
}
