#include <linux/build-salt.h>
#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(.gnu.linkonce.this_module) = {
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
__used __section(__versions) = {
	{ 0xfe9bc451, "module_layout" },
	{ 0x37a0cba, "kfree" },
	{ 0x6bc3fbc0, "__unregister_chrdev" },
	{ 0x4db83e31, "kmem_cache_alloc_trace" },
	{ 0x59cb71f8, "kmalloc_caches" },
	{ 0xa202bdab, "__register_chrdev" },
	{ 0x56470118, "__warn_printk" },
	{ 0xdcb764ad, "memset" },
	{ 0x12a4e128, "__arch_copy_from_user" },
	{ 0x88db9f48, "__check_object_size" },
	{ 0xd697e69a, "trace_hardirqs_on" },
	{ 0x6cbbfc54, "__arch_copy_to_user" },
	{ 0x3d8560e4, "cpu_hwcaps" },
	{ 0xec3d2e1b, "trace_hardirqs_off" },
	{ 0x4b50cb71, "cpu_hwcap_keys" },
	{ 0x14b89635, "arm64_const_caps_ready" },
	{ 0xc5850110, "printk" },
	{ 0x1fdc7df2, "_mcount" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "1219495AFDFE5106E7BF0F3");
