#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Vinay Kumar Dubey");
MODULE_DESCRIPTION("Code for loading and Unloading modules");

static int __init custom_module_init(void) {
    struct task_struct *task_list;
    static int count = 0;

    printk(KERN_INFO "Module loading done\n");

    
    for_each_process(task_list) {
        if(task_list->__state==TASK_RUNNING){
            count++;
        }
    }

    printk(KERN_INFO "Number of running processes: %d\n", count);

    return 0;
}

static void __exit custom_module_exit(void) {
    printk(KERN_INFO "Module Cleanup done\n");
}

module_init(custom_module_init);
module_exit(custom_module_exit);

