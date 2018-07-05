#include<linux/init.h>
#include<linux/module.h>
#include<linux/of.h>



MODULE_LICENSE("GPL");

struct device_node *np;
struct property *pp;

static int demo_init(void)
{
	int i;
	unsigned long *pv;
	unsigned char *pc;

	np = of_find_node_by_path("/demo1");	

	pp = of_find_property(np,"reg",NULL);

#if 1	
	printk("name = %s,length = %x\n",pp->name,pp->length);
	pv = pp->value;
	for(i = 0;i < pp->length / sizeof(long);i ++)
	{
		printk("%#x\n",be32_to_cpu(pv[i]));
	}
#endif
	pp = of_find_property(np,"mystr",NULL);
	printk("name = %s,length = %x\n",pp->name,pp->length);

	pc = pp->value;
#if 0
	for(i = 0;i < pp->length / sizeof("hello");i ++)
	{
		printk("%s\n",(char *)pc[i]);
		pc += sizeof("hello");
	}
#endif
	printk("%s\n",pc);
	return 0;
}

module_init(demo_init);

static void demo_exit(void)
{
	printk("demo_exit\n");
	return;
}
module_exit(demo_exit);
