#include <linux/module.h>

MODULE_LICENSE("GPL");

int init_module(void )
{
	printk("hello\n");
	return 0;
}
