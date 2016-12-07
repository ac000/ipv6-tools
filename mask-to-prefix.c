/*
 * mask-to-prefix.c - Given an IPv6 network mask display the prefix length.
 *
 *  Copyright (C) 2016	Andrew Clayton <andrew@digital-domain.net>
 *
 *  Licensed under the GNU General Public License Version 2 or
 *  the GNU Lesser General Public License Version 2.1
 *
 *  See GPLv2 & LGPLv2.1 in the source tree.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <arpa/inet.h>

/*
 * Based on code from http://www.keil.com/support/docs/194.htm
 *
 * Brian Kernighan method.
 */
static void mask_to_prefix(const char *mask)
{
	int i;
	uint8_t prefixlen = 0;
	struct in6_addr maskb;

	inet_pton(AF_INET6, mask, maskb.s6_addr);

	for (i = 0; i < 16; i++)
		for ( ; maskb.s6_addr[i] != 0; prefixlen++)
			maskb.s6_addr[i] &= maskb.s6_addr[i] - 1;

	printf("prefixlen : %u\n", prefixlen);
}

int main(int argc, char *argv[])
{
	if (argc < 2) {
		printf("Usage: mask-to-prefix <mask>\n");
		exit(EXIT_FAILURE);
	}

	mask_to_prefix(argv[1]);

	exit(EXIT_SUCCESS);
}
