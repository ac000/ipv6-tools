/*
 * mac-to-eui64.c - Generate a modified EUI-64 identifier for the given MAC
 * 		    address.
 *
 * Copyright (C) 2016		Andrew Clayton <andrew@digital-domain.net>
 *
 * Licensed under the GNU General Public License Version 2 or
 * the GNU Lesser General Public License Version 2.1
 *
 * See GPLv2 & LGPLv2.1 in the source tree.
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	long mac[8];
	int i;

	if (argc < 2) {
		fprintf(stderr, "Usage: mac-to-eui64 <MAC address>\n");
		exit(EXIT_FAILURE);
	}

	mac[0] = strtol(argv[1], NULL, 16);
	mac[1] = strtol(argv[1]+3, NULL, 16);
	mac[2] = strtol(argv[1]+6, NULL, 16);
	mac[3] = 0xff;
	mac[4] = 0xfe;
	mac[5] = strtol(argv[1]+9, NULL, 16);
	mac[6] = strtol(argv[1]+12, NULL, 16);
	mac[7] = strtol(argv[1]+15, NULL, 16);

	/* Toggle the (U/L) bit 0000 00*0 */
	mac[0] ^= 1 << 1;

	for (i = 0; i < 8; i++)
		printf("%02lx%s", mac[i], (i < 7) ? ":" : "");
	printf("\n");

	exit(EXIT_SUCCESS);
}
