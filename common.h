/*
 * common.h	- routines common to multiple files.
 *
 * Copyright (c) 2021 - 2023	Andrew Clayton <andrew@digital-domain.net>
 *
 * Licensed under the GNU General Public License Version 2 or
 * the GNU Lesser General Public License Version 2.1
 *
 * See GPLv2 & LGPLv2.1 in the source tree.
 */

#ifndef _COMMON_H_
#define _COMMON_H_

#include "short_types.h"

#define TXT_FMT_BOLD	"\033[1m"
#define TXT_FMT_END	"\033[0m"

extern void mac_to_eui64(const char *mac, u8 *buf);

#endif /* _COMMON_H_ */
