### Linux-Kernel-Module<br>

Step 1:design a simple Kernel Module and test it:<br>
1. Make a simple kernel module as below:<br>
2. Write a Makefile then make it, this will generate a lkm_example.ko, we will use it as a kernel module later on.<br>
3. Write a test function in Makefile that includes the insmod and rmmod lkm_example.ko so that we can do the above action with one command : $ make test.<br>

Step 2(Optional): In the previous example, you can only test the Kernel Module but you can not place breakpoints inside the Kernel Module for debugging. Use the techniques you learned in Assignment 1 to place a breakpoint in the user space (just before calling the Kernel Module APIs) and a breakpoint inside the Kernel Module that you developed. Please submit screenshots showing the CS register (if you are using x86 architecture or the correspondent register if you are using another architecture) showing that the code switched from user mode to kernel mode and back to the user mode.<br>
> Writing a program name “cat.c” in user space to get responses from the kernel_module, with this program, we can connect user space and kernel space. My major problem is where to set breakpoint inside cat.c and kernel_module, after few trying, I decided to set breakpoints in cat.c at line:8 and line:11, the former is right before getting the value from kernel, the latter is at the end of the program, and a breakpoint before printk in kernel_module, so that I can visit kernel space from user space then back to it, below is my implementation:
