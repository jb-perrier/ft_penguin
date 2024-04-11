#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

MODULE_LICENSE("GPL2");

static int __init insert(void)
{
	printk(KERN_INFO "keyboard_dd: Inserted keyboard !\n");
	return (0);
}

static void __exit remove(void)
{
	printk(KERN_INFO "keyboard_dd: Ejected keyboard !\n");
}

module_init(insert);
module_exit(remove);
