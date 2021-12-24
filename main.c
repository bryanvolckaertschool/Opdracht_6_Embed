/*
 *  hello-5.c - Demonstrates command line argument passing to a module.
 */
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/stat.h>
#include <linux/kthread.h>
#include <linux/delay.h>
#include <linux/gpio.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Bryan Volckaert");

/* Task handle to identify thread */
static struct task_struct *toggle1 = NULL;
static struct task_struct *toggle2 = NULL;

static int gpio_array[2];
static int level_array[2];
static int toggle_array[2];

static int arr_argc = 0;

static struct gpio gpio_output[] = {
    {17, GPIOF_OUT_INIT_LOW, "LED 1"},
    {27, GPIOF_OUT_INIT_LOW, "LED 2"},
};

static int toggle_thread1(void *data)
{
    printk(KERN_INFO "%s\n", __func__);
    printk(KERN_INFO "toggle thread speed = %d\n", toggle_array[0] * 100);

    // loop until killed ...
    while (!kthread_should_stop())
    {
        gpio_set_value(gpio_output[0].gpio, !gpio_get_value(gpio_output[0].gpio));

        mdelay(toggle_array[0] * 100);
    }

    return 0;
}

static int toggle_thread2(void *data)
{
    printk(KERN_INFO "%s\n", __func__);
    printk(KERN_INFO "toggle thread speed = %d\n", toggle_array[0] * 100);

    // loop until killed ...
    while (!kthread_should_stop())
    {
        gpio_set_value(gpio_output[1].gpio, !gpio_get_value(gpio_output[1].gpio));

        mdelay(toggle_array[1] * 100);
    }

    return 0;
}

/*
 * module_param_array(name, type, num, perm);
 * The first param is the parameter's (in this case the array's) name
 * The second param is the data type of the elements of the array
 * The third argument is a pointer to the variable that will store the number 
 * of elements of the array initialized by the user at module loading time
 * The fourth argument is the permission bits
 */

module_param_array(gpio_array, int, &arr_argc, 0000);
MODULE_PARM_DESC(gpio_array, "An array of integers");

module_param_array(level_array, int, &arr_argc, 0000);
MODULE_PARM_DESC(level_array, "An array of integers");

module_param_array(toggle_array, int, &arr_argc, 0000);
MODULE_PARM_DESC(toggle_array, "An array of integers");

static int __init gpio_blink_init(void)
{
    int i;
    int ret;

    ret = gpio_request_array(gpio_output, ARRAY_SIZE(gpio_output));
    if (ret)
    {
        printk(KERN_ERR "Unable to request GPIOs: %d\n", ret);
    }

    printk(KERN_INFO " %d argumenten.\n", arr_argc);
    for (i = 0; i < arr_argc; i++)
    {

        gpio_output[i].gpio = gpio_array[i];
        gpio_set_value(gpio_output[i].gpio, level_array[i]);
        printk(KERN_INFO "GPIO%d: %d met snelheid %d.\n", gpio_output[i].gpio, level_array[i], toggle_array[i]);
    }

    toggle1 = kthread_create(toggle_thread1, NULL, "toggle_thread1");
    toggle2 = kthread_create(toggle_thread2, NULL, "toggle_thread2");

    if (toggle2 && toggle1)
    {
        wake_up_process(toggle1);
        wake_up_process(toggle2);
        printk(KERN_INFO "Created threads\n");
    }
    else
    {
        printk(KERN_ERR "Problems with threads\n");
    }

    return 0;
}

static void __exit gpio_blink_exit(void)
{
    int i;
    printk(KERN_INFO "Goodbye, world 5\n");

    if (toggle1 && toggle2)
    {
        kthread_stop(toggle1);
        kthread_stop(toggle2);
    }

    // turn all LEDs off
    for (i = 0; i < arr_argc; i++)
    {
        gpio_set_value(gpio_output[i].gpio, 0);
    }

    // unregister all GPIOs
    gpio_free_array(gpio_output, arr_argc);
}

module_init(gpio_blink_init);
module_exit(gpio_blink_exit);