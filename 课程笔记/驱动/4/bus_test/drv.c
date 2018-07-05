#include "head.h"

int drv_test(struct dev *info)
{
	return info->a + info->b;
}

struct drv mydrv = {
	.name = "18031",
	.p = drv_test,
};
