/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * (C) Copyright 2015 Hans de Goede <hdegoede@redhat.com>
 */

#ifndef _SUNXI_CPU_H
#define _SUNXI_CPU_H

#if defined(CONFIG_MACH_SUN9I)
#include <asm/arch/cpu_sun9i.h>
#elif defined(CONFIG_SUN50I_GEN_H6)
#include <asm/arch/cpu_sun50i_h6.h>
#elif defined(CONFIG_SUNXI_GEN_NCAT2)
#include <asm/arch/cpu_sunxi_ncat2.h>
#else
#include <asm/arch/cpu_sun4i.h>
#endif

#define SOCID_A64	0x1689
#define SOCID_H3	0x1680
#define SOCID_V3S	0x1681
#define SOCID_H5	0x1718
#define SOCID_R40	0x1701

#if defined(CONFIG_SUNXI_RTC_FEL_ENTRY_GPR) && (CONFIG_SUNXI_RTC_FEL_ENTRY_GPR >= 0)
#ifdef CONFIG_MACH_SUN8I_H3
#define SUNXI_FEL_ENTRY_ADDRESS 0xffff0020
#define SUNXI_RTC_GPR_OFFSET 0x100
#define SUNXI_FEL_REG  (SUNXI_RTC_BASE + SUNXI_RTC_GPR_OFFSET + CONFIG_SUNXI_RTC_FEL_ENTRY_GPR * 4)
#endif
#endif
#ifndef __ASSEMBLY__
void set_rtc_fel_flag(void);
#endif

#endif /* _SUNXI_CPU_H */
