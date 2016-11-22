/*
 * mac-type.c	- Check the U/L bit in a MAC address.
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
	long mac;

	if (argc < 2) {
		fprintf(stderr, "Usage: mac-type <MAC address>\n");
		exit(EXIT_FAILURE);
	}

	mac = strtol(argv[1], NULL, 16);

	/*
	 * Test the second-least-significant bit of the first byte
	 * of the address.
	 */
	if (mac & 0x02)
		printf("U/L bit is set. Address is locally administered.\n");
	else
		printf("U/L bit is NOT set. Address is universally administered.\n");

	exit(EXIT_SUCCESS);
}
