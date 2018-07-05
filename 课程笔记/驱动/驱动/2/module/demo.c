#include <linux/module.h>
#include <linux/init.h>

int value;
module_param(value,int,0600);

char *p;
module_param(p,charp,0600);

char str[10];
module_param_string(mystr,str,10,0600);

int array[5];
int n;
module_param_array(array,int,&n,0400);

int demo_init(void) //自定义的一个模块入口
{
	int i;

	printk("hello world init\n");
	printk("value = %d\n",value);
	printk("p = %s\n",p);
	printk("str = %s\n",str);

	for(i = 0;i < n;i ++)
	{
		printk("%d ",array[i]);
	}
	printk("\n");
	return 0;
}

void demo_exit(void)
{
	printk("hello world exit\n");
	return;
}

module_init(demo_init);
module_exit(demo_exit);

MODULE_LICENSE("GPL");
