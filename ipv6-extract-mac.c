/*
 * ipv6-extract-mac.c	- Extract the MAC address from an IPv6 address,
 * 			  e.g SLAAC
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
#include <stdint.h>
#include <string.h>

int main(int argc, char *argv[])
{
	uint8_t mac[6];
	uint16_t val;
	int i;
	char *ptr;
	char *tmp;

	if (argc < 2) {
		fprintf(stderr, "Usage: ipv6-extract-mac <IPv6 address>\n");
		exit(EXIT_FAILURE);
	}

	ptr = strstr(argv[1], "::");
	if (ptr) {
		ptr += 2;
	} else {
		tmp = argv[1];
		for (i = 0; i < 4; i++) {
			ptr = strchr(tmp, ':');
			if (!ptr)
				goto invalid_address;
			ptr++;
			tmp = ptr;
		}
	}

	val = strtoul(ptr, NULL, 16);
	mac[0] = val >> 8;
	/* Toggle the (U/L) bit 0000 00*0 */
	mac[0] ^= 1 << 1;
	mac[1] = val & 0xff;
	tmp = ptr;
	ptr = strchr(tmp, ':');
	if (!ptr)
		goto invalid_address;
	ptr++;
	val = strtoul(ptr, NULL, 16);
	mac[2] = val >> 8;

	tmp = ptr;
	ptr = strchr(tmp, ':');
	if (!ptr)
		goto invalid_address;
	ptr++;
	val = strtoul(ptr, NULL, 16);
	mac[3] = val & 0xff;

	tmp = ptr;
	ptr = strchr(tmp, ':');
	if (!ptr)
		goto invalid_address;
	ptr++;
	val = strtoul(ptr, NULL, 16);
	mac[4] = val >> 8;
	mac[5] = val & 0xff;

	if (mac[0] & 0x02 || mac[0] & 0x01)
		printf("WARNING: This address may NOT be based off a MAC address.\n");
	for (i = 0; i < 6; i++)
		printf("%02x%s", mac[i], (i < 5) ? ":" : "");
	printf("\n");

	exit(EXIT_SUCCESS);

invalid_address:
	printf("This address is too short to be based off a MAC address.\n");

	exit(EXIT_FAILURE);
}
