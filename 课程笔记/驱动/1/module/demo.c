#include <linux/module.h>

MODULE_LICENSE("GPL");

//static为了避免和其他的模块冲突
//如果使用了__init则驱动模块会被编译到.init.text分段中
static int __init demo_init(void)  //自定义加载函数
{
	printk("18031 init\n");
	return 0;
}

module_init(demo_init);//将自定义加载函数和默认加载函数绑定

//如果直接编译进内核镜像中，则这段程序不参与编译
static void __exit demo_exit(void)
{
	printk("18031 exit\n");
	return;
}
module_exit(demo_exit);
