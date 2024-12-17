#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/elfnote-lto.h>
#include <linux/export-internal.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

#ifdef CONFIG_UNWINDER_ORC
#include <asm/orc_header.h>
ORC_HEADER;
#endif

BUILD_SALT;
BUILD_LTO_INFO;

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
	{ 0xf04d38a, "single_open" },
	{ 0xbabe4320, "kern_path" },
	{ 0xf3def9fb, "vfs_statfs" },
	{ 0xfd8f7d4c, "seq_printf" },
	{ 0xf0fdf6cb, "__stack_chk_fail" },
	{ 0x9b965a55, "remove_proc_entry" },
	{ 0xf47eefb5, "seq_read" },
	{ 0x99e5f1d4, "seq_lseek" },
	{ 0x7fc5be11, "single_release" },
	{ 0x1e3f6320, "param_ops_charp" },
	{ 0xbdfb6dbb, "__fentry__" },
	{ 0xcdd3b2be, "proc_create" },
	{ 0x122c3a7e, "_printk" },
	{ 0x5b8239ca, "__x86_return_thunk" },
	{ 0x9bb6f1bb, "module_layout" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "8271C21B2FE374B9CB6A49D");