#include <linux/module.h>

void cleanup_module(void)
{
	printk("exit\n");
	return;
}
