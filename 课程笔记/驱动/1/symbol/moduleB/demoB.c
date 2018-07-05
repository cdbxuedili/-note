#include <linux/module.h>

extern int glovalue;
extern int add(int,int);

static int __init demoB_init(void)
{
	printk("glovalue = %d\n",glovalue);
	printk("add = %d\n",add(10,20));
	printk("demoB_init\n");
	return 0;
}
module_init(demoB_init);

static void __exit demoB_exit(void)
{
	printk("demoB_exit\n");

}
module_exit(demoB_exit);

MODULE_LICENSE("GPL");

