#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

#define INFO_FILE "alejo_memory"

static struct proc_dir_entry *alejo_info_file;

static int alejo_infor_show(struct seq_file *theFile, void *v)
{
    seq_printf(theFile, "Llamada a la syscall 548\n");
    //aqui va todo lo de imprimir lo de la ram
    return 0;
}

static into alejo_info_open(struct inode *inode, struct file *file)
{
    return single_open(file, alejo_info_show, NULL);
}

static const struct proc_ops alejo_memory_ops = {
    .proc_open = alejo_info_open,
    .proc_read = seq_read,
    .proc_lseek = seq_lseek,
    .proc_release = single_release,
};

static int __init alejo_memory_init(void)
{
    printk(KERN_INFO "SYSCALL1: Inicializando modulo\n");
    alejo_info_file = proc_create(INFO_FILE, 0, NULL, &alejo_memory_ops);
    if (!alejo_info_file)
    {
        printk(KERN_ERR "SYSCALL2: Error al crear el archivo en /proc\n");
        return -ENOMEM;
    }
    return 0;
}

static void __exit alejo_memory_exit(void)
{
    printk(KERN_INFO "SYSCALL2: deteniendo el modulo\n");
    proc_remove(alejo_memory);
}

module_init(alejo_memory_init);
module_exit(alejo_memory_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ALEJO");
MODULE_DESCRIPTION("Modulo para la syscall2");
MODULE_VERSION("0.1");
