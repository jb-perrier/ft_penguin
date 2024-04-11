#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/miscdevice.h>
#include <linux/uaccess.h>

MODULE_LICENSE("MIT");
MODULE_AUTHOR("jperrier");
MODULE_DESCRIPTION("a05 module");

#define BUF "jperrier"
#define BUF_LEN 8

static struct miscdevice device;

static ssize_t module_read(struct file *f, char *buffer, size_t length, loff_t *offset)
{
	char *read_from = BUF + *offset;
	size_t read_num = length < (BUF_LEN - *offset) ? length : (BUF_LEN - *offset);

	if (read_num == 0)
		return 0;

	ssize_t res = copy_to_user(buffer, read_from, read_num);
	if (res == read_num) {
		res = -EIO;
	} else {
		*offset = BUF_LEN - res;
		res = read_num - res;
	}

	return res;
}

static ssize_t module_write(struct file *f, const char *buf, size_t len, loff_t *offset)
{
	char mybuf[BUF_LEN];

	if (len != BUF_LEN)
		return -EINVAL;

	ssize_t res = copy_from_user(mybuf, buf, BUF_LEN);
	if (res != 0)
		return -EINVAL;
	
	if (strncmp(mybuf, BUF, BUF_LEN) == 0)
		res = BUF_LEN;
	else
		res = -EINVAL;

	return res;
}

static struct file_operations fops = {
  .read = module_read,
  .write = module_write,
};

int init_module(void)
{
	device.minor = MISC_DYNAMIC_MINOR;
	device.name = "fortytwo";
	device.fops = &fops;
	return misc_register(&device);
}

void cleanup_module(void)
{
	misc_deregister(&device);
}


