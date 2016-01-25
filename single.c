#include <linux/module.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>

static dev_t firstDev; // Global variable for the first device number
static struct cdev c_dev; // Global variable for the character device structure
static struct class *cl; // Global variable for the device class

static int my_open(struct inode *, struct file *);
static int my_close(struct inode *, struct file *);
static ssize_t my_read(struct file *, char __user *, size_t, loff_t *);
static ssize_t my_write(struct file *, const char __user *buf, size_t, loff_t *);
static struct file_operations mydev_fops =
{
    .owner = THIS_MODULE,
    .open = my_open,
    .release = my_close,
    .read = my_read,
    .write = my_write
};

static int __init mydev_init(void) /* Constructor */
{
    int ret;
    struct device *dev_ret;

    if ((ret = alloc_chrdev_region(&firstDev, 0, 1, "mydevname")) < 0) {
        printk(KERN_INFO "fail alloc_chrdev_region, code: %d\n", ret);
        goto fail_alloc_chardev_region;
    }
    if (IS_ERR(cl = class_create(THIS_MODULE, "mycharclass"))) {
        ret = PTR_ERR(cl);
        printk(KERN_INFO "fail class_create, code: %d\n", ret);
        goto fail_class_create;
    }
    if (IS_ERR(dev_ret = device_create(cl, NULL, firstDev, NULL, "mydevname"))) {
        ret = PTR_ERR(dev_ret);
        printk(KERN_INFO "fail device_create, code: %d\n", ret);
        goto fail_device_create;
    }
    cdev_init(&c_dev, &mydev_fops);
    if ((ret = cdev_add(&c_dev, firstDev, 1)) < 0)
        goto fail_cdev_add;
    printk(KERN_INFO "mydev sucessfuly created\n");
    return 0;

/* carefully backout on failure(s) */
fail_cdev_add:
    device_destroy(cl, firstDev);
fail_device_create:
    class_destroy(cl);
fail_class_create:
    unregister_chrdev_region(firstDev, 1);
fail_alloc_chardev_region:
    return ret;
}

static void __exit mydev_exit(void) /* Destructor */
{
    cdev_del(&c_dev);
    device_destroy(cl, firstDev);
    class_destroy(cl);
    unregister_chrdev_region(firstDev, 1);
    printk(KERN_INFO "mydev unregistered\n");
}

static int my_open(struct inode *i, struct file *f)
{
    printk(KERN_INFO "Driver: open()\n");
    return 0;
}
static int my_close(struct inode *i, struct file *f)
{
    printk(KERN_INFO "Driver: close()\n");
    return 0;
}
static ssize_t my_read(struct file *f, char __user *buf, size_t len, loff_t *off)
{
    printk(KERN_INFO "Driver: read()\n");
    return 0;
}
static ssize_t my_write(struct file *f, const char __user *buf, size_t len,
    loff_t *off)
{
    printk(KERN_INFO "Driver: write()\n");
    return len;
}

module_init(mydev_init);
module_exit(mydev_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("George Wayne");
MODULE_DESCRIPTION("my First Character Driver");
MODULE_VERSION("1.0");
