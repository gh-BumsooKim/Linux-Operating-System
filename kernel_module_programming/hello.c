#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

int __init init_hello(void){
	printk(KERN_ALERT "Hello World \n");
	//printk("<1> Hello Wrold \n");
	return 0;
}

void __exit exit_hello(void){
	printk(KERN_ALERT "Good-bye \n");
}

// Log Level Configuration
//cat /proc/sys/kernel/printk

// Kernel Resource File
//ll /lib/modules

module_init(init_hello);
module_exit(exit_hello);
