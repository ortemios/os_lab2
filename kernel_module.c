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
#include <linux/mount.h>
#include <linux/namei.h>
#include <linux/path.h>
#include <linux/sched/cputime.h>
#include <linux/path.h>

#define BUFFER_SIZE 128

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Lavrov Artyem");
MODULE_DESCRIPTION("Lab2");
MODULE_VERSION("1.0");

static struct dentry *kmod_dir;
static char vfs_path[BUFFER_SIZE];
static int pid;

static int write_output(struct seq_file *file, void *data) {
    struct task_struct* task = get_pid_task(find_get_pid(pid), PIDTYPE_PID);
    if (task) {
        u64 utime, stime;
        task_cputime(task, &utime, &stime);
        seq_printf(file, "task_cputime.utime=%d\n", utime);
        seq_printf(file, "task_cputime.stime=%d\n", stime);
        seq_printf(file, "task_cputime.sum_exec_runtime=%d\n", stime + utime);
    } else {
        seq_printf(file, "task_cputime: invalid pid\n");
    }

    struct path path;
    if (kern_path(vfs_path, LOOKUP_FOLLOW, &path) == 0) {
        seq_printf(file, "mnt.mnt_root=%p\n", path.mnt->mnt_root);
        seq_printf(file, "mnt.mnt_sb=%p\n", path.mnt->mnt_sb);
        seq_printf(file, "mnt.mnt_flags=%x\n", path.mnt->mnt_flags);
    } else {
        seq_printf(file, "vfsmount: invalid path\n");
    }
    return 0;
}

static ssize_t write_structures(struct file *file, const char __user *buffer, size_t length, loff_t *ptr_offset) {
    char input_buf[BUFFER_SIZE];
    copy_from_user(input_buf, buffer, length);
    sscanf(input_buf, "task_cputime (pid): %d, vfsmount (path): %s",  &pid, vfs_path);
    single_open(file, write_output, NULL);
    return strlen(input_buf);
}

static struct file_operations fops = {
        .read = seq_read,
        .write = write_structures,
};

static int __init mod_init(void) {
    kmod_dir = debugfs_create_dir("lab", NULL);
    debugfs_create_file("2", 0644, kmod_dir, NULL, &fops);
    return 0;
}


static void __exit mod_exit(void) {
    debugfs_remove_recursive(kmod_dir);
}

module_init(mod_init);
module_exit(mod_exit);