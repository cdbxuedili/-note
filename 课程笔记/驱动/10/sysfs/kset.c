#include <linux/module.h>
#include <linux/init.h>
#include <linux/kobject.h>
#include <linux/string.h>
#include <linux/sysfs.h>
#include <linux/slab.h>

struct demo_obj {
	struct kobject kobj;
	int demo;
};
#define to_demo_obj(x) container_of(x, struct demo_obj, kobj)

struct demo_attribute {
	struct attribute attr;
	ssize_t (*show)(struct demo_obj *demo, struct demo_attribute *attr, char *buf);
	ssize_t (*store)(struct demo_obj *demo, struct demo_attribute *attr, const char *buf, size_t count);
};
#define to_demo_attr(x) container_of(x, struct demo_attribute, attr)

static ssize_t demo_attr_show(struct kobject *kobj,
			     struct attribute *attr,
			     char *buf)
{
	struct demo_attribute *attribute;
	struct demo_obj *demo;

	attribute = to_demo_attr(attr);
	demo = to_demo_obj(kobj);

	return attribute->show(demo, attribute, buf);
}

static ssize_t demo_attr_store(struct kobject *kobj,
			      struct attribute *attr,
			      const char *buf, size_t len)
{
	struct demo_attribute *attribute;
	struct demo_obj *demo;

	attribute = to_demo_attr(attr);//指向了demo_attribute
	demo = to_demo_obj(kobj);

	return attribute->store(demo, attribute, buf, len);
}

static const struct sysfs_ops demo_sysfs_ops = {
	.show = demo_attr_show,
	.store = demo_attr_store,
};

static ssize_t demo_show(struct demo_obj *demo_obj, struct demo_attribute *attr,
			char *buf)
{
	return sprintf(buf, "%d\n", demo_obj->demo);
}

static ssize_t demo_store(struct demo_obj *demo_obj, struct demo_attribute *attr,
			 const char *buf, size_t count)
{
	sscanf(buf, "%d", &demo_obj->demo);
	return count;
}

static struct demo_attribute demo_attribute = __ATTR(xxx, 0666, demo_show, demo_store);

static struct attribute *demo_default_attrs[] = {
	&demo_attribute.attr,
	NULL,
};

static struct kobj_type demo_ktype = {
	.sysfs_ops = &demo_sysfs_ops,
	.default_attrs = demo_default_attrs,
};

static struct kset *demo_kset;
static struct demo_obj *demo_obj;

static struct demo_obj *create_demo_obj(const char *name)
{
	struct demo_obj *demo;
	int retval;

	demo = kzalloc(sizeof(*demo), GFP_KERNEL);

	demo->kobj.kset = demo_kset;

	retval = kobject_init_and_add(&demo->kobj, &demo_ktype, NULL, "%s", name);

	return demo;
}

static void destroy_demo_obj(struct demo_obj *demo)
{
	kobject_put(&demo->kobj);
}

static int  demo_init(void)
{
	demo_kset = kset_create_and_add("kset_demo", NULL,NULL);
	demo_obj = create_demo_obj("demo");

	return 0;
}

static void demo_exit(void)
{
	destroy_demo_obj(demo_obj);
	kset_unregister(demo_kset);
}

module_init(demo_init);
module_exit(demo_exit);
MODULE_LICENSE("GPL");
