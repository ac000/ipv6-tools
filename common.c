/*
 * common.c	- routines common to multiple files.
 *
 * Copyright (c) 2021	Andrew Clayton <andrew@digital-domain.net>
 *
 * Licensed under the GNU General Public License Version 2 or
 * the GNU Lesser General Public License Version 2.1
 *
 * See GPLv2 & LGPLv2.1 in the source tree.
 */

#include <stdlib.h>

#include "short_types.h"

void mac_to_eui64(const char *mac, u8 *buf)
{
	buf[0] = strtoul(mac, NULL, 16);
	buf[1] = strtoul(mac+3, NULL, 16);
	buf[2] = strtoul(mac+6, NULL, 16);
	buf[3] = 0xff;
	buf[4] = 0xfe;
	buf[5] = strtoul(mac+9, NULL, 16);
	buf[6] = strtoul(mac+12, NULL, 16);
	buf[7] = strtoul(mac+15, NULL, 16);

	/* Toggle the (U/L) bit 0000 00*0 */
	buf[0] ^= 1 << 1;
}
