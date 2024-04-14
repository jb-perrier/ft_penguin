#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/debugfs.h>
#include <linux/jiffies.h>
#include "id.c"
#include "foo.c"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("jperrier");
MODULE_DESCRIPTION("a07 module");

static struct dentry *debugfs_root;

int init_module(void)
{	
	debugfs_root = debugfs_create_dir("fortytwo", NULL);
	if (!debugfs_root)
		return -ENOENT;

	mutex_init(&foo_mutex);

	// return value remove in recent linux version
	debugfs_create_u64("jiffies", 0444, debugfs_root, (u64*)(&jiffies));
	
	if (!debugfs_create_file("id", 0666, debugfs_root, NULL, &id_fops)
		|| !debugfs_create_file("foo", 0644, debugfs_root, NULL, &foo_fops))
		return -ENOENT;

	return 0;
}

void cleanup_module(void)
{	
	debugfs_remove_recursive(debugfs_root);
}
