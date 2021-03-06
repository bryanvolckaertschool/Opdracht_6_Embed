#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0xbd97005b, "module_layout" },
	{ 0x9e9fbfdf, "param_array_ops" },
	{ 0x7b66b44c, "param_ops_int" },
	{ 0x9dfdf722, "gpio_free_array" },
	{ 0x223fc350, "kthread_stop" },
	{ 0x977035dc, "wake_up_process" },
	{ 0x31556c9c, "kthread_create_on_node" },
	{ 0x8574ca6c, "gpio_request_array" },
	{ 0xba4c293, "gpiod_set_raw_value" },
	{ 0x8f411754, "gpiod_get_raw_value" },
	{ 0xe30324cf, "gpio_to_desc" },
	{ 0xb3f7646e, "kthread_should_stop" },
	{ 0x8e865d3c, "arm_delay_ops" },
	{ 0xc5850110, "printk" },
	{ 0xb1ad28e0, "__gnu_mcount_nc" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "2BD2010E9197ACA8DB09FC8");
