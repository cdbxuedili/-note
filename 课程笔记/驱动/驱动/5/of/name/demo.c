#include<linux/init.h>
#include<linux/module.h>
#include<linux/of.h>

#if 0

demo1{
	reg = <0x123456 0x4>;
	mystr = "hello","world";

	demo2{
		reg = <0x12345678 0x8>;
	};
};

#endif

MODULE_LICENSE("GPL");

struct device_node *p_parent;
struct device_node *p_child;
struct property *pp; 


static int demo_init(void)
{
	int i;
	unsigned long *pv;

	p_parent = of_find_node_by_path("/demo1");

	p_child = of_find_node_by_name(p_parent,"demo2");	

	pp = of_find_property(p_child,"reg",NULL);
	
	pv = pp->value;
	for(i = 0;i < pp->length/sizeof(long);i ++)
	{
		printk("%x\n",be32_to_cpu(pv[i]));
	}
	return 0;
}

module_init(demo_init);

static void demo_exit(void)
{
	printk("demo_exit\n");
	return;
}
module_exit(demo_exit);
