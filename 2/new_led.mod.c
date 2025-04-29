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
	{ 0xcd32f847, "__platform_driver_register" },
	{ 0x141e757c, "_dev_info" },
	{ 0xe4477d56, "gpiod_set_value" },
	{ 0xe08736b, "devm_kmalloc" },
	{ 0xd5c94a99, "devm_gpiod_get" },
	{ 0x9136568d, "devm_led_classdev_register_ext" },
	{ 0x16736258, "_dev_err" },
	{ 0x9deb2665, "platform_driver_unregister" },
	{ 0x67a35d9, "module_layout" },
};

MODULE_INFO(depends, "");

MODULE_ALIAS("of:N*T*Crpi,led");
MODULE_ALIAS("of:N*T*Crpi,ledC*");

MODULE_INFO(srcversion, "8F95F63D973DE8E4398A6DF");
