# Linux Kernel PWN


- pahole (for viewing and manipulating data structure layout)
- process struct
- task struct

looks like a good one to go through
- https://snyk.io/blog/kernel-privilege-escalation/
cred reference in task_struct
- https://elixir.bootlin.com/linux/v5.18.17/source/include/linux/sched.h#L1042



task struct: https://elixir.bootlin.com/linux/v6.6.16/source/include/linux/sched.h#L743



## Resources

Example code on module to walk through task list
- https://developer.ibm.com/tutorials/l-linux-process-management/

Writing Linux Kernel Modules
- https://sysprog21.github.io/lkmpg/

Intro (good starting point and scripts for challenges)
- https://lkmidas.github.io/posts/20210123-linux-kernel-pwn-part-1/

example kernel pwn challenges
- https://github.com/smallkirby/kernelpwn?tab=readme-ov-file


pahole (for showing and manipulating data structs)
- https://linux.die.net/man/1/pahole

/dev/ptmx (pseudo terminal stuff)
- https://linux.die.net/man/4/ptmx
/proc/kallsyms (contains kernel symbol table)
- https://man7.org/linux/man-pages/man5/proc_kallsyms.5.html

