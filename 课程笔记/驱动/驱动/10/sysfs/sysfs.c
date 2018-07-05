#include <linux/module.h>



static char kbuf[1024] = {0};
static ssize_t my_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    char info[]="my_show is called\n";
    return scnprintf(buf,sizeof(info),info);
}

static ssize_t my_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{
    printk("%s is called\n",__func__);
    strncpy(kbuf,buf,count);
    printk("user_buf:%s,count:%d|after copy,kbuf:%s\n",buf,count,kbuf);
    return count;
}

//show是name，就是sys中的文件名
static struct kobj_attribute my_sysfs_read =__ATTR(show, S_IRUSR, my_show, NULL);

static struct kobj_attribute my_sysfs_write =__ATTR(write, S_IWUSR, NULL,my_store);

static struct attribute *my_sysfs_attr[] = {
    &my_sysfs_read.attr,
    &my_sysfs_write.attr,
    NULL,
};

static struct attribute_group my_sysfs_attr_group = {
    .name = "sub_my_attr",      //不写这个成员就不会创建子文件夹
    .attrs = my_sysfs_attr,
};

struct kobject *my_kobj = NULL;
int mysys_init(void)
{
	int ret;
    my_kobj = kobject_create_and_add("my_sysfs", NULL);
    ret = sysfs_create_group(my_kobj, &my_sysfs_attr_group);
	return 0;
}

void mysys_exit(void)
{
    sysfs_remove_group(my_kobj, &my_sysfs_attr_group);
    kobject_put(my_kobj);
}
module_init(mysys_init);
module_exit(mysys_exit);
MODULE_LICENSE("GPL");
