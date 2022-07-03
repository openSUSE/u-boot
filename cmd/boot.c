// SPDX-License-Identifier: GPL-2.0+
/*
 * (C) Copyright 2000-2003
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 */

/*
 * Misc boot support
 */
#include <common.h>
#include <command.h>
#include <net.h>

#ifdef CONFIG_CMD_GO

/* Allow ports to override the default behavior */
__attribute__((weak))
unsigned long do_go_exec(ulong (*entry)(int, char * const []), int argc,
				 char *const argv[])
{
	return entry (argc, argv);
}

static int do_go(struct cmd_tbl *cmdtp, int flag, int argc, char *const argv[])
{
	ulong	addr, rc;
	int     rcode = 0;

	if (argc < 2)
		return CMD_RET_USAGE;

	addr = hextoul(argv[1], NULL);

	printf ("## Starting application at 0x%08lX ...\n", addr);
	flush();

	/*
	 * pass address parameter as argv[0] (aka command name),
	 * and all remaining args
	 */
	rc = do_go_exec ((void *)addr, argc - 1, argv + 1);
	if (rc != 0) rcode = 1;

	printf ("## Application terminated, rc = 0x%lX\n", rc);
	return rcode;
}
#endif

#if defined(CONFIG_ROCKCHIP_BOOT_MODE_REG) && CONFIG_ROCKCHIP_BOOT_MODE_REG
#define RBROM
#include <asm/arch-rockchip/boot_mode.h>
static int do_reboot_brom(struct cmd_tbl *cmdtp, int flag, int argc, char * const argv[])
{
	set_back_to_bootrom_dnl_flag();
	do_reset(NULL, 0, 0, NULL);

	return 0;
}
#endif

#ifdef CONFIG_ARCH_SUNXI
#include <asm/arch-sunxi/cpu.h>
#ifdef SUNXI_FEL_REG
#define RBROM
static int do_reboot_brom(struct cmd_tbl *cmdtp, int flag, int argc, char * const argv[])
{
	set_rtc_fel_flag();
	do_reset(NULL, 0, 0, NULL);

	return 0;
}
#endif
#endif

/* -------------------------------------------------------------------- */

#ifdef CONFIG_CMD_GO
U_BOOT_CMD(
	go, CONFIG_SYS_MAXARGS, 1,	do_go,
	"start application at address 'addr'",
	"addr [arg ...]\n    - start application at address 'addr'\n"
	"      passing 'arg' as arguments"
);
#endif

#ifdef RBROM
U_BOOT_CMD(
	rbrom, 1, 0,	do_reboot_brom,
	"Perform RESET of the CPU and enter boot rom",
	""
);
#endif

U_BOOT_CMD(
	reset, 2, 0,	do_reset,
	"Perform RESET of the CPU",
	"- cold boot without level specifier\n"
	"reset -w - warm reset if implemented"
);

#ifdef CONFIG_CMD_POWEROFF
U_BOOT_CMD(
	poweroff, 1, 0,	do_poweroff,
	"Perform POWEROFF of the device",
	""
);
#endif
