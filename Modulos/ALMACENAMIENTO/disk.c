#include <linux/module.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/fs.h>
#include <linux/statfs.h>
#include <linux/uaccess.h>
#include <linux/namei.h> 

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ALEJO");
MODULE_DESCRIPTION("Estadísticas de almacenamiento en GB para una partición específica");
MODULE_VERSION("1.0");

static char *partition = "/"; 
module_param(partition, charp, 0444);
MODULE_PARM_DESC(partition, "Ruta de la partición (por ejemplo, / o /mnt)");

static int write_storage_stats(struct seq_file *file, void *v)
{
    struct kstatfs stats;
    struct path path;


    if (kern_path(partition, LOOKUP_FOLLOW, &path))
    {
        seq_printf(file, "{\n\"error\": \"Error al acceder a la partición: %s\"\n}\n", partition);
        return 0;
    }

    if (vfs_statfs(&path, &stats))
    {
        seq_printf(file, "{\n\"error\": \"Error al obtener estadísticas de la partición: %s\"\n}\n", partition);
        return 0;
    }

    unsigned long long total_space_gb = (stats.f_blocks * stats.f_bsize) >> 30; 
    unsigned long long free_space_gb = (stats.f_bfree * stats.f_bsize) >> 30;  
    unsigned long long available_space_gb = (stats.f_bavail * stats.f_bsize) >> 30; 

    seq_printf(file, "{\n");
    seq_printf(file, "\"partition\": \"%s\",\n", partition);
    seq_printf(file, "\"total_space_gb\": %llu,\n", total_space_gb);
    seq_printf(file, "\"free_space_gb\": %llu,\n", free_space_gb);
    seq_printf(file, "\"available_space_gb\": %llu\n", available_space_gb);
    seq_printf(file, "}\n");

    return 0;
}

static int open_storage_stats(struct inode *inode, struct file *file)
{
    return single_open(file, write_storage_stats, NULL);
}

static const struct proc_ops storage_stats_ops = {
    .proc_open = open_storage_stats,
    .proc_read = seq_read,
    .proc_lseek = seq_lseek,
    .proc_release = single_release,
};

static int __init storage_stats_init(void)
{
    // Crear el archivo en /proc
    struct proc_dir_entry *entry = proc_create("disk_so2_201602855", 0444, NULL, &storage_stats_ops);
    if (!entry)
    {
        pr_err("Error al crear el archivo /proc/disk_so2_201602855\n");
        return -ENOMEM;
    }

    pr_info("Carga de módulo de estadísticas . Partición: %s\n", partition);
    return 0;
}

static void __exit storage_stats_exit(void)
{
    // Remover el archivo de /proc
    remove_proc_entry("disk_so2_201602855", NULL);
    pr_info("descarga de módulo de estadísticas\n");
}

module_init(storage_stats_init);
module_exit(storage_stats_exit);
