#include <linux/module.h>

static int glovalue = 100;
EXPORT_SYMBOL(glovalue);

static int add(int a,int b)
{
	return a + b;
}
EXPORT_SYMBOL_GPL(add);

static int __init demoA_init(void)
{
	printk("demoA_init\n");
	return 0;
}
module_init(demoA_init);

static void __exit demoA_exit(void)
{
	printk("demoA_exit\n");

}
module_exit(demoA_exit);

MODULE_LICENSE("GPL");
