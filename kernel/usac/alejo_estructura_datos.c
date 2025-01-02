#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include <linux/errno.h>
#include <linux/mutex.h>
#include <linux/list.h>
#include <linux/resource.h>
#include <linux/sched.h>

typedef struct memory_limitation {
    pid_t pid;
    size_t memory_limit;
    struct list_head list;
} memory_limitation_t;

static LIST_HEAD(memory_limit_list);
static DEFINE_MUTEX(memory_limit_mutex);

static int find_memory_entry(pid_t process_pid, memory_limitation_t **out_entry) {
    memory_limitation_t *temp;
    list_for_each_entry(temp, &memory_limit_list, list) {
        if (temp->pid == process_pid) {
            *out_entry = temp;
            return 0;
        }
    }
    return -ENOENT;
}

static int set_task_memory_limit(struct task_struct *task, size_t memory_limit) {
    struct rlimit rl = {
        .rlim_cur = memory_limit,
        .rlim_max = memory_limit,
    };

    get_task_struct(task);
    if (security_task_setrlimit(task, RLIMIT_AS, &rl)) {
        put_task_struct(task);
        return -EPERM;
    }
    task->signal->rlim[RLIMIT_AS] = rl;
    put_task_struct(task);
    return 0;
}

SYSCALL_DEFINE2(alejo_add_memory_limit, pid_t, process_pid, size_t, memory_limit) {
    struct task_struct *task;
    memory_limitation_t *entry;

    if (process_pid <= 0 || memory_limit == 0)
        return -EINVAL;

    task = find_task_by_vpid(process_pid);
    if (!task)
        return -ESRCH;

    mutex_lock(&memory_limit_mutex);

    if (!find_memory_entry(process_pid, &entry)) {
        mutex_unlock(&memory_limit_mutex);
        return -101; 
    }

    entry = kmalloc(sizeof(*entry), GFP_KERNEL);
    if (!entry) {
        mutex_unlock(&memory_limit_mutex);
        return -ENOMEM;
    }

    entry->pid = process_pid;
    entry->memory_limit = memory_limit;
    list_add_tail(&entry->list, &memory_limit_list);

    if (set_task_memory_limit(task, memory_limit)) {
        list_del(&entry->list);
        kfree(entry);
        mutex_unlock(&memory_limit_mutex);
        return -EPERM;
    }

    mutex_unlock(&memory_limit_mutex);
    return 0;
}

SYSCALL_DEFINE3(alejo_get_memory_limits, struct memory_limitation __user *, u_processes_buffer, size_t, max_entries, int __user *, processes_returned) {
    memory_limitation_t *temp;
    size_t count = 0;

    if (!u_processes_buffer || !processes_returned || max_entries == 0)
        return -EINVAL;

    struct memory_limitation *k_buffer = kmalloc_array(max_entries, sizeof(*k_buffer), GFP_KERNEL);
    if (!k_buffer)
        return -ENOMEM;

    mutex_lock(&memory_limit_mutex);

    list_for_each_entry(temp, &memory_limit_list, list) {
        if (count >= max_entries)
            break;
        k_buffer[count++] = *temp;
    }

    mutex_unlock(&memory_limit_mutex);

    if (copy_to_user(u_processes_buffer, k_buffer, count * sizeof(*k_buffer)) ||
        copy_to_user(processes_returned, &count, sizeof(count))) {
        kfree(k_buffer);
        return -EFAULT;
    }

    kfree(k_buffer);
    return 0;
}

SYSCALL_DEFINE2(alejo_update_memory_limit, pid_t, process_pid, size_t, memory_limit) {
    struct task_struct *task;
    memory_limitation_t *entry;

    if (process_pid <= 0 || memory_limit == 0)
        return -EINVAL;

    task = find_task_by_vpid(process_pid);
    if (!task)
        return -ESRCH;

    mutex_lock(&memory_limit_mutex);

    if (find_memory_entry(process_pid, &entry)) {
        mutex_unlock(&memory_limit_mutex);
        return -102;
    }

    if (task->mm && task->mm->total_vm > (memory_limit >> PAGE_SHIFT)) {
        mutex_unlock(&memory_limit_mutex);
        return -100;
    }

    entry->memory_limit = memory_limit;

    if (set_task_memory_limit(task, memory_limit)) {
        mutex_unlock(&memory_limit_mutex);
        return -EPERM;
    }

    mutex_unlock(&memory_limit_mutex);
    return 0;
}

SYSCALL_DEFINE1(alejo_remove_memory_limit, pid_t, process_pid) {
    memory_limitation_t *entry;

    if (process_pid <= 0)
        return -EINVAL;

    mutex_lock(&memory_limit_mutex);

    if (find_memory_entry(process_pid, &entry)) {
        mutex_unlock(&memory_limit_mutex);
        return -ENOENT;
    }

    list_del(&entry->list);
    kfree(entry);

    mutex_unlock(&memory_limit_mutex);
    return 0;
}
