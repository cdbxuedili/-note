#include <linux/module.h>
#include <linux/init.h>

static int glo_val = 101;
EXPORT_SYMBOL_GPL(glo_val);

static int fun(int a,int b)
{
	return a + b;
}
EXPORT_SYMBOL_GPL(fun);
//EXPORT_SYMBOL(fun);

int demo_init(void) //自定义的一个模块入口
{
	printk("hello world init\n");
	return 0;
}
module_init(demo_init);

void demo_exit(void)
{
	printk("hello world exit\n");
	return;
}
module_exit(demo_exit);
MODULE_LICENSE("GPL");
