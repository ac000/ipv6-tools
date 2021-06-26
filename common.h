/*
 * common.h	- routines common to multiple files.
 *
 * Copyright (c) 2021	Andrew Clayton <andrew@digital-domain.net>
 *
 * Licensed under the GNU General Public License Version 2 or
 * the GNU Lesser General Public License Version 2.1
 *
 * See GPLv2 & LGPLv2.1 in the source tree.
 */

#include "short_types.h"

extern void mac_to_eui64(const char *mac, u8 *buf);
