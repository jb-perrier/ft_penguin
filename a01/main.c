#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("MIT");
MODULE_AUTHOR("jperrier");
MODULE_DESCRIPTION("Hello World module");

int init_module(void)
{
	printk(KERN_INFO "Hello world !\n");
	return 0;
}

void cleanup_module(void)
{
	printk(KERN_INFO "Cleaning up module.\n");
}
