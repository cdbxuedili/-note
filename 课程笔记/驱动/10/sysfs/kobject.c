#include<linux/module.h>
#include<linux/init.h>

struct kobject *demo_kobj;
//struct kobject *child_kobj;

char kbuf[1024];
char *p;
ssize_t demo_show(struct kobject *kobj,struct kobj_attribute *attr,char *ubuf)
{
	char info[] = "kernel show is called\n";
	return sprintf(ubuf,"%s",info);
}

ssize_t demo_store(struct kobject *kobj,struct kobj_attribute *attr,const char *ubuf,size_t count)
{
	strncpy(kbuf,ubuf,count);

	printk("recv from user %s\n",kbuf);
	return count;
}

#if 0
struct kobj_attribute demo_kobj_attr_show = {
	.attr = {
		.name = "show",//shou就是一个属性文件名
		.mode = S_IRUSR,
	},
	.show = demo_show,
};

struct kobj_attribute demo_kobj_attr_store = {
	.attr = {
		.name = "store",//也是一个属性文件名
		.mode = S_IWUSR,
	},
	.store = demo_store,
};
#endif

//show和store是属性文件名
struct kobj_attribute demo_kobj_attr_show = __ATTR(show,S_IRUSR,demo_show,NULL);
struct kobj_attribute demo_kobj_attr_store = __ATTR(store,S_IWUSR,NULL,demo_store);

struct attribute *demo_attr[] = {
	&demo_kobj_attr_show.attr,
	&demo_kobj_attr_store.attr,
	NULL,
	
};

struct attribute_group demo_attr_grp = {
//	.name = "sub_dir",//如果没有初始化name成员则show和store属性文件会创建在my_kobj目录下
	.attrs = demo_attr,
};

int demo_init(void)
{
	int ret;
	/*单独执行这个函数只会创建my_kobj文件夹，如果第二个参数为NULL默认创建在/sys目录下
	返回一个struct kobject *指针来代表my_kobj文件夹,如果要生成子目录或者子文件还
	要继续封装struct kobj_attribute结构体和struct attribute结构体*/
	demo_kobj = kobject_create_and_add("my_kobj",NULL);
//	child_kobj = kobject_create_and_add("child",demo_kobj);
	
	ret = sysfs_create_group(demo_kobj,&demo_attr_grp);
	if(ret)
		kobject_put(demo_kobj);
	return ret;
}
module_init(demo_init);

void demo_exit(void)
{
	kobject_put(demo_kobj);
	return;
}
module_exit(demo_exit);
MODULE_LICENSE("GPL");
