#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/pci.h>
#include <linux/debugfs.h>
#include <linux/fs.h>
#include <linux/seq_file.h>
#include <linux/pid.h>
#include <linux/mm.h>
#include <linux/mm_types.h>
#include <linux/sched.h>
#include <linux/types.h>
#include <linux/namei.h>
#include <linux/path.h>
#include <linux/mutex.h>
#include <linux/iio/iio.h>
#include <linux/ioctl.h>
#include <linux/cdev.h>
#include <linux/pci.h>
#include <linux/iio/machine.h>
#include <linux/mfd/lp8788.h>
#include <linux/iio/driver.h>
#include <linux/module.h>
#include <linux/platform_device.h>

#define BUFFER_SIZE 128

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Korepanov Matvey");
MODULE_DESCRIPTION("Lab2");
MODULE_VERSION("1.0");

static struct dentry *kmod_dir;
static int pid;
static int vendor_id, device_id;
static struct mutex lock;

struct lp8788_adc {
	struct lp8788 *lp;
	struct iio_map *map;
	struct mutex lock;
};


static int write_output(struct seq_file *file, void *data) {
    struct task_struct* task = get_pid_task(find_get_pid(pid), PIDTYPE_PID);
    if (task) {
        seq_printf(file, "task_struct.pid=%d\n", task->pid);
    } else {
        seq_printf(file, "task_struct: invalid pid\n");
    }

    struct pci_dev *dev = pci_get_device(PCI_ANY_ID, PCI_ANY_ID, NULL);
    if (dev) {
        struct iio_dev *indio_dev = container_of(dev->device, struct iio_dev, dev);
        struct lp8788_adc *adc = iio_priv(indio_dev);
        struct iio_map *iio_map = adc->map;
        seq_printf(file, "iio_map.adc_channel_label=%p\n", iio_map->adc_channel_label);
        seq_printf(file, "iio_map.consumer_dev_name=%p\n", iio_map->consumer_dev_name);
        seq_printf(file, "iio_map.consumer_channel=%x\n", iio_map->consumer_channel);
    } else {
        seq_printf(file, "iio_map: invalid vendor_id:device_id\n");
    }
    return 0;
}

static ssize_t write_structures(struct file *file, const char __user *buffer, size_t length, loff_t *ptr_offset) {
    mutex_lock(&lock);
    char input_buf[BUFFER_SIZE];
    copy_from_user(input_buf, buffer, length);
    sscanf(input_buf, "pid: %d, vendor_id: %d, device_id: %d",  &pid, &vendor_id, &device_id);
    single_open(file, write_output, NULL);
    mutex_unlock(&lock);
    return strlen(input_buf);
}

static struct file_operations fops = {
        .read = seq_read,
        .write = write_structures,
};

static int __init mod_init(void) {
    mutex_init(&lock);
    kmod_dir = debugfs_create_dir("lab", NULL);
    debugfs_create_file("2", 0644, kmod_dir, NULL, &fops);
    return 0;
}


static void __exit mod_exit(void) {
    debugfs_remove_recursive(kmod_dir);
}

module_init(mod_init);
module_exit(mod_exit);
