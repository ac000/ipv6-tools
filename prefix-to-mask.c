/*
 * prefix-to-mask.c - Given an IPv6 prefix length display the network mask.
 *
 *  Copyright (C) 2016 - 2017	Andrew Clayton <andrew@digital-domain.net>
 *
 *  Licensed under the GNU General Public License Version 2 or
 *  the GNU Lesser General Public License Version 2.1
 *
 *  See GPLv2 & LGPLv2.1 in the source tree.
 */

#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>

#include "short_types.h"

/*
 * Based on code from nginx.
 */
static void prefix_to_mask(u8 prefixlen)
{
	int i;
	struct in6_addr maskb;
	char masks[INET6_ADDRSTRLEN];

	/* Create a mask based on prefixlen */
	for (i = 0; i < 16; i++) {
		u8 s = (prefixlen > 8) ? 8 : prefixlen;

		prefixlen -= s;
		maskb.s6_addr[i] = (0xffu << (8 - s));
	}

	inet_ntop(AF_INET6, maskb.s6_addr, masks, INET6_ADDRSTRLEN);
	printf("comp    %s\nuncomp  ", masks);

	for (i = 0; i < 15; i += 2) {
		printf("%02x%02x", maskb.s6_addr[i], maskb.s6_addr[i + 1]);
		if (i < 14)
			printf(":");
	}
	printf("\n");
}

int main(int argc, char *argv[])
{
	if (argc < 2) {
		printf("Usage: prefix-to-mask <prefixlen>\n");
		exit(EXIT_FAILURE);
	}

	prefix_to_mask(atoi(argv[1]));

	exit(EXIT_SUCCESS);
}
