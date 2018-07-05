#include"head.h"

int add(struct dev *info)
{
	return info->a + info->b;
}

struct drv mydrv = {
	.name = "hello",
	.p = add,
};
