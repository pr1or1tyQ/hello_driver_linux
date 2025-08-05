# Makefile for Linux Kernel Module and Userspace Application
# Designed for:
# - Kernel module source in ./kern_mod/
# - Userspace application source in ./user_space/

# --- Kernel Module Configuration ---
KERNEL_MODULE_DIR := kern_mod
KERNEL_MODULE_NAME := cred_mod
obj-m += $(KERNEL_MODULE_DIR)/$(KERNEL_MODULE_NAME).o

# --- Userspace Application Configuration ---
USERSPACE_APP_DIR := user_space
USERSPACE_APP_NAME := kmsg_reader
USERSPACE_SRC := $(USERSPACE_APP_DIR)/$(USERSPACE_APP_NAME).c
USERSPACE_BIN := $(USERSPACE_APP_DIR)/$(USERSPACE_APP_NAME)

# --- Targets ---

# Default target: builds both the kernel module and the userspace application
all: modules $(USERSPACE_BIN)

# Target to build the kernel module (delegates to kernel build system)
modules:
	@echo "Building kernel module in $(KERNEL_MODULE_DIR)/..."
	# -C: Change directory to kernel build tree
	# M=$(PWD)/$(KERNEL_MODULE_DIR): Specify where our module source is
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD)/$(KERNEL_MODULE_DIR) modules

# Target to build the userspace application
$(USERSPACE_BIN): $(USERSPACE_SRC)
	@echo "Building userspace application in $(USERSPACE_APP_DIR)/..."
	gcc $(USERSPACE_SRC) -o $(USERSPACE_BIN)

# Clean target: cleans both kernel module and userspace application build artifacts
clean: clean_modules clean_userspace

# Clean kernel module artifacts
clean_modules:
	@echo "Cleaning kernel module artifacts from $(KERNEL_MODULE_DIR)/..."
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD)/$(KERNEL_MODULE_DIR) clean

# Clean userspace application artifacts
clean_userspace:
	@echo "Cleaning userspace application artifacts from $(USERSPACE_APP_DIR)/..."
	rm -f $(USERSPACE_BIN)
