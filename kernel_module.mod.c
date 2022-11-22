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
	{ 0x64491f21, "module_layout" },
	{ 0xae69b833, "seq_read" },
	{ 0x7faac491, "debugfs_remove_recursive" },
	{ 0x70e3f03f, "debugfs_create_file" },
	{ 0x29479260, "debugfs_create_dir" },
	{ 0xcbd4898c, "fortify_panic" },
	{ 0x56470118, "__warn_printk" },
	{ 0xa916b694, "strnlen" },
	{ 0xf3e69aa4, "single_open" },
	{ 0xbcab6ee6, "sscanf" },
	{ 0x362ef408, "_copy_from_user" },
	{ 0x88db9f48, "__check_object_size" },
	{ 0xdecd0b29, "__stack_chk_fail" },
	{ 0x19f9da2b, "kern_path" },
	{ 0xcc4e6c1, "seq_printf" },
	{ 0x44cf0c1d, "get_pid_task" },
	{ 0x3991af8f, "find_get_pid" },
	{ 0xbdfb6dbb, "__fentry__" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "88227E950880D03B698EDFE");
