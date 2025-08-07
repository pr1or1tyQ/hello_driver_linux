# Hello Kernel Driver (Linux)

### Practice Linux Kernel Modules to get better at kernel pwn challenges

Note: this is the starting draft

#### todo 
- clean up kernel_pwn_notes.md and update with things found
- practice different methods to communicate between kernel and user space
  - event driven (udev/uevents)
  - ioctl
  - shared memory space (mmap)
  - syscalls to device files exposed by driver
  - netlink socekts

## Usage
- compile the module `make`
- load the module `sudo insmod cred_mod.ko`
- [optional] unload module `sudo rmmod cred_mod`
