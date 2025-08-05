#include <linux/module.h>    // Required for kernel modules
#include <linux/kernel.h>    // Required for KERN_INFO
#include <linux/init.h>      // Required for module_init and module_exit macros
#include <linux/cred.h>      // Required for the 'struct cred' definition
#include <linux/sched.h>     // Required for 'current' macro and 'task_struct'

// // Module metadata
// MODULE_LICENSE("GPL");
// MODULE_AUTHOR("Your Name/AI");
// MODULE_DESCRIPTION("A simple kernel module to print the current process's credential struct.");

/**
 * @brief Retrieves the current process's credential struct and print when module is loaded
 */
static int __init cred_module_init(void)
{
    const struct cred *creds; // Pointer to the credential struct
    struct task_struct *task; // Pointer to the current task struct

    printk(KERN_INFO "cred_module: Loading module...\n");

    // Get the current task_struct
    task = current;

    // Get the credentials of the current task
    // get_task_cred() increments the reference count, so put_cred() must be called later.
    // However, for 'current' task, 'task->cred' is directly accessible and already ref-counted.
    // Using task->cred directly is common for the current process.
    creds = task->cred;

    if (creds) {
        printk(KERN_INFO "cred_module: --- Current Process Credentials ---\n");
        printk(KERN_INFO "cred_module: Real UID (ruid): %d\n", __kuid_val(creds->uid));
        printk(KERN_INFO "cred_module: Effective UID (euid): %d\n", __kuid_val(creds->euid));
        printk(KERN_INFO "cred_module: Saved UID (suid): %d\n", __kuid_val(creds->suid));
        printk(KERN_INFO "cred_module: Filesystem UID (fsuid): %d\n", __kuid_val(creds->fsuid));
        printk(KERN_INFO "cred_module: Real GID (rgid): %d\n", __kgid_val(creds->gid));
        printk(KERN_INFO "cred_module: Effective GID (egid): %d\n", __kgid_val(creds->egid));
        printk(KERN_INFO "cred_module: Saved GID (sgid): %d\n", __kgid_val(creds->sgid));
        printk(KERN_INFO "cred_module: Filesystem GID (fsgid): %d\n", __kgid_val(creds->fsgid));

        // Print capabilities (inheritable, permitted, effective)
        // Capabilities are bitmasks, so printing them in hex is useful.
        printk(KERN_INFO "cred_module: Capabilities (inheritable): 0x%x\n", creds->cap_inheritable.cap[0]);
        printk(KERN_INFO "cred_module: Capabilities (permitted): 0x%x\n", creds->cap_permitted.cap[0]);
        printk(KERN_INFO "cred_module: Capabilities (effective): 0x%x\n", creds->cap_effective.cap[0]);
        printk(KERN_INFO "cred_module: -----------------------------------\n");
    } else {
        printk(KERN_ERR "cred_module: Failed to retrieve credentials for current process.\n");
    }

    printk(KERN_INFO "cred_module: Module loaded successfully.\n");
    return 0; // Indicate successful loading
}

/**
 * @brief This function is called when the module is unloaded.
 */
static void __exit cred_module_exit(void)
{
    printk(KERN_INFO "cred_module: Unloading module.\n");
}

// Register the module's init and exit functions
module_init(cred_module_init);
module_exit(cred_module_exit);
