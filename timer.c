#include <linux/module.h>	// included for all kernel modules
#include <linux/kernel.h>	// included for KERN_INFO
#include <linux/init.h>	  // included for __init and __exit macros
#include <linux/fs.h>

#include <linux/version.h>

#include <linux/timer.h>
//#include <signal.h>
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

MODULE_LICENSE("GPL");
MODULE_AUTHOR("MML");
MODULE_DESCRIPTION("A Simple kernel_hello_irq module");

//static int calc_result = 0;
typedef unsigned int uint;
static uint  prints_count = 4;

struct timer_list my_timer;
module_param(prints_count, uint, (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH));
MODULE_PARM_DESC(prints_count, "An integer , prints_count");

volatile int num_of_prints = 0;
static const int delay_in_seconds = 4;


void my_timer_function(unsigned long data)
{
	int new_delay = delay_in_seconds*HZ;   
	if (++num_of_prints < prints_count)
		mod_timer(&my_timer, jiffies + new_delay);  /* new expiration */
	else
		printk(KERN_INFO "======== done timers. kernel_hello_irq module ===========\n");

	printk(KERN_INFO "\n" "Hello from linux" ": ===== current: num_of_prints = %d\n", num_of_prints);
}

static int __init kernel_hello_irq_init(void)
{
	int ret = 0;
	int delay;
	printk(KERN_INFO "======== kernel_hello_irq module installed. ===========\n");
	printk(KERN_INFO "prints_count : %d\n", prints_count);
	init_timer(&my_timer);
	delay = delay_in_seconds*HZ;         /* 4 seconds from now */
	my_timer.expires = jiffies + delay;    /* timer expires in delay ticks */
	my_timer.data = 0;                     /* zero is passed to the timer handler */
	my_timer.function = my_timer_function;       /* function to run when timer expires */
	add_timer(&my_timer);

//err:
	return ret;// Non-zero return means that the module couldn't be loaded.

}

static void __exit kernel_hello_irq_cleanup(void)
{
	del_timer_sync(&my_timer);
	printk(KERN_INFO "========= kernel_hello_irq module removed ==================\n");
}

module_init(kernel_hello_irq_init);
module_exit(kernel_hello_irq_cleanup);
