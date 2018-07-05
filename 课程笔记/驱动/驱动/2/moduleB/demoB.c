#include <linux/module.h>
#include <linux/init.h>

extern int glo_val;
extern int fun(int,int);

int demo_init(void) //自定义的一个模块入口
{
	printk("hello world init\n");

	printk("glo_val = %d\n",glo_val);
	printk("fun = %d\n",fun(10,20));
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
