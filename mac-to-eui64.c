/*
 * mac-to-eui64.c - Generate a modified EUI-64 identifier for the given MAC
 * 		    address.
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
	u8 mac[8];
	int i;

	if (argc < 2)
		scanf("%19s", macstr);
	else
		snprintf(macstr, sizeof(macstr), "%s", argv[1]);

	mac[0] = strtoul(macstr, NULL, 16);
	mac[1] = strtoul(macstr+3, NULL, 16);
	mac[2] = strtoul(macstr+6, NULL, 16);
	mac[3] = 0xff;
	mac[4] = 0xfe;
	mac[5] = strtoul(macstr+9, NULL, 16);
	mac[6] = strtoul(macstr+12, NULL, 16);
	mac[7] = strtoul(macstr+15, NULL, 16);

	/* Toggle the (U/L) bit 0000 00*0 */
	mac[0] ^= 1 << 1;

	printf("Modified EUI-64 : ");
	for (i = 0; i < 8; i++)
		printf("%02x%s", mac[i], (i < 7) ? ":" : "");
	printf("\n(SLAAC Host)    : ::");
	for (i = 0; i < 8; i += 2)
		printf("%02x%02x%s", mac[i], mac[i + 1], i+1 < 7 ? ":" : "");
	printf("\n(link-local)    : fe80::");
	for (i = 0; i < 8; i += 2)
		printf("%02x%02x%s", mac[i], mac[i + 1], i+1 < 7 ? ":" : "");
	printf("\n");

	exit(EXIT_SUCCESS);
}
