#include <linux/init.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

#define INFO_FILE "infoSYSCALL2"

static struct proc_dir_entry *alejo_info_file;

static int alejo_info_open(struct inode *inode,struct file *file)
{
    return single_open(file, alejo_info_open, NULL);
}

static alejo_info_show(struct seq_file *theFile, void *v)
{
    seq_printf(theFile, "Hola, soy la syscall2\n");
    return 0;
}


static const struct syscall2 alejo_syscall2 =
{
    .proc_open    = syscall2_open,
    .proc_read    = seq_read,
    .proc_lseek   = seq_lseek,
    .proc_release = single_release,
};


static int __init syscall2_init(void)
{
    printk(KERN_INFO "SYSCALL2: Inicializando modulo\n");
    proc_entry = proc_create(INFO_FILE, 0444, NULL, &alejo_syscall2);
    if (!proc_entry)
    {
        printk(KERN_ERR "SYSCALL2: Error al crear el archivo en /proc\n");
        return -ENOMEM;
    }
    return 0;
};

static void __exit syscall2_exit(void)
{
    printk(KERN_INFO "SYSCALL2: deteniendo el modulo\n");
    proc_remove(infoSYSCALL2);
};

module_init(syscall2_init);
module_exit(syscall2_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ALEJO");
MODULE_DESCRIPTION("Modulo para la syscall2");
MODULE_VERSION("0.1");