#include <linux/module.h>
#include <linux/init.h>

#if 0
//模块默认入口
int init_module(void)//在内核中行参是void不能省略
{
	printk("hello world init\n");
	return 0;//驱动中，成功返回0，失败返回一个负数值
}

void cleanup_module(void)
{
	printk("hello world exit\n");
	return ;
}
#endif

//注意:习惯将自定义的入口名称以_init结尾
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
