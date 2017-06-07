#include <linux/module.h>	// included for all kernel modules
#include <linux/kernel.h>	// included for KERN_INFO
#include <linux/init.h>	  // included for __init and __exit macros
#include <linux/fs.h>

#include <linux/version.h>

#include <linux/timer.h>
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

MODULE_LICENSE("GPL");
MODULE_AUTHOR("MML");
MODULE_DESCRIPTION("A Simple kernel_hello_irq module");

//static int calc_result = 0;
static unsigned int prints_count = 4;

module_param(prints_count, unsigned int, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
MODULE_PARM_DESC(prints_count, "An integer , prints_count");

//----------------------------------------
#define LEN_MSG 160
static char buf_msg[ LEN_MSG + 1 ] = "Hello from module!\n";

static int __init kernel_hello_irq_init(void)
{
	int ret = 0;
	printk(KERN_INFO "======== kernel_hello_irq module installed ,===========\n");
err:
	return ret;// Non-zero return means that the module couldn't be loaded.

}

static void __exit kernel_hello_irq_cleanup(void)
{

	sysfs_cleanup();
	printk(KERN_INFO "========= kernel_hello_irq module removed ==================\n");
}

module_init(kernel_hello_irq_init);
module_exit(kernel_hello_irq_cleanup);
