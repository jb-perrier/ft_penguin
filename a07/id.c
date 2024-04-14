#include <linux/kernel.h>
#include <linux/uaccess.h>

#define BUF "jperrier"
#define BUF_LEN 8

static ssize_t id_op_read(struct file *f, char *buffer, size_t length, loff_t *offset)
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

static ssize_t id_op_write(struct file *f, const char *buf, size_t len, loff_t *offset)
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

static struct file_operations id_fops = {
  .read = id_op_read,
  .write = id_op_write,
};
