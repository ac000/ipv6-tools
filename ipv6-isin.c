/*
 * ipv6-isin.c - Given an IPv6 network/prefix and an IPv6 address, determine
 * 		 if the address falls within the given network.
 *
 *  Copyright (C) 2015 - 2017	Andrew Clayton <andrew@digital-domain.net>
 *
 *  Licensed under the GNU General Public License Version 2 or
 *  the GNU Lesser General Public License Version 2.1
 *
 *  See GPLv2 & LGPLv2.1 in the source tree.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#include "short_types.h"

/*
 * Based on code from nginx.
 */
static void ipv6_isin(const char *network, u8 prefixlen, const char *addr)
{
	int i;
	unsigned char netb[sizeof(struct in6_addr)];
	unsigned char maskb[sizeof(struct in6_addr)];
	unsigned char addrb[sizeof(struct in6_addr)];

	inet_pton(AF_INET6, network, netb);
	inet_pton(AF_INET6, addr, addrb);

	/* Create a mask based on prefixlen */
	for (i = 0; i < 16; i++) {
		u8 s = (prefixlen > 8) ? 8 : prefixlen;

		prefixlen -= s;
		maskb[i] = (0xffu << (8 - s));
	}

	for (i = 0; i < 16; i++) {
		if ((addrb[i] & maskb[i]) != netb[i]) {
			printf("No\n");
			return;
		}
	}

	printf("Yes\n");
}

int main(int argc, char *argv[])
{
	u8 prefixlen;
	char *ptr;

	if (argc < 3) {
		printf("Usage: ipv6-isin network/prefix address\n");
		exit(EXIT_FAILURE);
	}

	prefixlen = atoi(strchr(argv[1], '/') + 1);
	ptr = strchr(argv[1], '/');
	*ptr = '\0';
	ipv6_isin(argv[1], prefixlen, argv[2]);

	exit(EXIT_SUCCESS);
}
