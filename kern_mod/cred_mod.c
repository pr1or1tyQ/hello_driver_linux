#include <linux/module.h>   
#include <linux/kernel.h>    
#include <linux/init.h>      
#include <linux/cred.h>      // Required for the 'struct cred' definition
#include <linux/sched.h>     // Required for 'current' macro and 'task_struct'
#include <linux/types.h>     

/**
 * @brief This function is called when the module is loaded.
 * It retrieves the current process's credential struct and prints its details.
 */
static int __init cred_module_init(void)
{
    const struct cred *creds; // Pointer to the credential struct
    struct task_struct *task; // Pointer to the current task struct

    printk(KERN_INFO "cred_mod: Loading module...\n"); // Updated module name in printk

    // Get the current task_struct
    task = current;

    // Get the credentials of the current task
    // Using task->cred directly is common for the current process.
    creds = task->cred;

    if (creds) {
        printk(KERN_INFO "cred_mod: --- Current Process Credentials ---\n");
        printk(KERN_INFO "cred_mod: Real UID (ruid): %d\n", __kuid_val(creds->uid));
        printk(KERN_INFO "cred_mod: Effective UID (euid): %d\n", __kuid_val(creds->euid));
        printk(KERN_INFO "cred_mod: Saved UID (suid): %d\n", __kuid_val(creds->suid));
        printk(KERN_INFO "cred_mod: Filesystem UID (fsuid): %d\n", __kuid_val(creds->fsuid));
        printk(KERN_INFO "cred_mod: Real GID (rgid): %d\n", __kgid_val(creds->gid));
        printk(KERN_INFO "cred_mod: Effective GID (egid): %d\n", __kgid_val(creds->egid));
        printk(KERN_INFO "cred_mod: Saved GID (sgid): %d\n", __kgid_val(creds->sgid));
        printk(KERN_INFO "cred_mod: Filesystem GID (fsgid): %d\n", __kgid_val(creds->fsgid));

        // Print capabilities (inheritable, permitted, effective)
        printk(KERN_INFO "cred_mod: Capabilities (inheritable): 0x%x\n", creds->cap_inheritable);
        printk(KERN_INFO "cred_mod: Capabilities (permitted): 0x%x\n", creds->cap_permitted);
        printk(KERN_INFO "cred_mod: Capabilities (effective): 0x%x\n", creds->cap_effective);
        printk(KERN_INFO "cred_mod: -----------------------------------\n");
    } else {
        printk(KERN_ERR "cred_mod: Failed to retrieve credentials for current process.\n");
    }

    printk(KERN_INFO "cred_mod: Module loaded successfully.\n");
    return 0;
}

/**
 * @brief This function is called when the module is unloaded.
 */
static void __exit cred_module_exit(void)
{
    printk(KERN_INFO "cred_mod: Unloading module.\n"); // Updated module name in printk
}

// Register the module's init and exit functions
module_init(cred_module_init);
module_exit(cred_module_exit);
