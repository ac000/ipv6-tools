/*
 * mac-type.c	- Check the U/L (LG) & IG bits in a MAC address.
 *
 * Copyright (C) 2016 - 2017	Andrew Clayton <andrew@digital-domain.net>
 *
 * Licensed under the GNU General Public License Version 2 or
 * the GNU Lesser General Public License Version 2.1
 *
 * See GPLv2 & LGPLv2.1 in the source tree.
 */

#include <stdio.h>
#include <stdlib.h>

#include "short_types.h"

int main(int argc, char *argv[])
{
	char macstr[20];
	u8 mac;

	if (argc < 2)
		scanf("%19s", macstr);
	else
		snprintf(macstr, sizeof(macstr), "%s", argv[1]);

	mac = strtoul(macstr, NULL, 16);
	/*
	 * Test for the U/L (LG) bit which is the second-least-significant
	 * bit of the first byte of the address.
	 */
	if (mac & 0x02)
		printf("U/L (LG) bit is set. Address is locally administered.\n");
	else
		printf("U/L (LG) bit is NOT set. Address is universally administered.\n");

	/*
	 * Test for the IG bit which is the least-significant bit of the
	 * first byte of the address.
	 */
	if (mac & 0x01)
		printf("IG bit is set. Broadcast address.\n");
	else
		printf("IG bit is NOT set. Unicast address.\n");

	exit(EXIT_SUCCESS);
}
