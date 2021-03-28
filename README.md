### Linux-Kernel-Module<br>

Step 1:design a simple Kernel Module and test it:<br>

1. Make a simple kernel module as below:<br>
```
mkdir ~/src/lkm_example
cd ~/src/lkm_example
```
```
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
MODULE_LICENSE(“GPL”);
MODULE_AUTHOR(“Robert W. Oliver II”);
MODULE_DESCRIPTION(“A simple example Linux module.”);
MODULE_VERSION(“0.01”);
static int __init lkm_example_init(void) {
 printk(KERN_INFO “Hello, World!\n”);
 return 0;
}
static void __exit lkm_example_exit(void) {
 printk(KERN_INFO “Goodbye, World!\n”);
}
module_init(lkm_example_init);
module_exit(lkm_example_exit);
```
3. Write a Makefile then make it, this will generate a lkm_example.ko, we will use it as a kernel module later on.<br>
```
obj-m += lkm_example.o
all:
 make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean:
 make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
```
5. Write a test function in Makefile that includes the insmod and rmmod lkm_example.ko so that we can do the above action with one command : $ make test.<br>

Step 2: In the previous example, you can only test the Kernel Module but you can not place breakpoints inside the Kernel Module for debugging. Use the techniques you learned in Assignment 1 to place a breakpoint in the user space (just before calling the Kernel Module APIs) and a breakpoint inside the Kernel Module that you developed. Please submit screenshots showing the CS register (if you are using x86 architecture or the correspondent register if you are using another architecture) showing that the code switched from user mode to kernel mode and back to the user mode.<br>
> Writing a program name “cat.c” in user space to get responses from the kernel_module, with this program, we can connect user space and kernel space. My major problem is where to set breakpoint inside cat.c and kernel_module, after few trying, I decided to set breakpoints in cat.c at line:8 and line:11, the former is right before getting the value from kernel, the latter is at the end of the program, and a breakpoint before printk in kernel_module, so that I can visit kernel space from user space then back to it, below is my implementation:
1. First open qemu and install the kernel module name “kernel_user.ko” on it.<br>
2. Set breakpoint at line:8 and line:11 in “cat.c” as I mentioned above<br>
3. At kernel_module.ko, set breakpoint before printk, so that I can stop at this point to monitor the kernel space <br>
4. When the program stop at first breakpoint at “cat.c”, by using $info register, it shows that I am currently in the user space since cs register is 51<br>
5. When program hit the first breakpoint in “cat.c”, pause QEMU with ctrl + c, I am now can use gdb in kernel space, use $info register to show my current cs register value, 16, proving that it is in kernel space<br>
6. Continue the previous breakpoint, I am now back to qemu in user space, use $info register to show cs register with value 51 which proves that we are back to user space<br>
7. After going through all of the breakpoints, $info register again shows that we run the whole program and complete the visiting between user and kernel.<br>
