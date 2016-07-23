/*
 * ipv6-range.c - Given an IPv6 network address with prefix, calculate the
 * 		  range of IPs available.
 *
 *  Copyright (C) 2015 - 2016	Andrew Clayton <andrew@digital-domain.net>
 *
 *  Licensed under the GNU General Public License Version 2 or
 *  the GNU Lesser General Public License Version 2.1
 *
 *  See GPLv2 & LGPLv2.1 in the source tree.
 */

#define _DEFAULT_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <arpa/inet.h>

/*
 * Based on code from https://github.com/peczenyj/IPv6SubnetCalc/
 */
static void ipv6_range(const char *network, unsigned short prefixlen)
{
	struct in6_addr ip6b;
	struct in6_addr ip6eb;
	struct in6_addr ip6sb;
	int i;
	int imask = 128 - prefixlen;
	uint64_t networks = UINT64_MAX;
	char net_s[60] = "\0";

	inet_pton(AF_INET6, network, &ip6b);

	for (i = 15; i >= 0; i--) {
		int j = (imask > 8) ? 8 : imask;
		unsigned char x = (1 << j) - 1;

		ip6sb.s6_addr[i] = ip6b.s6_addr[i] & ~x;
		ip6eb.s6_addr[i] = ip6b.s6_addr[i] | x;
		imask -= j;
	}

	/*
	 * For a prefix length of < 64, calculate the number of /64 networks
	 * the given network provides. E.g a /48 provides 65536 /64's
	 */
	if (prefixlen < 64)
		snprintf(net_s, sizeof(net_s), "(%u /56 networks, "
				"%zu /64 networks)", 1 << (56 - prefixlen),
				(networks >> prefixlen) + 1);

	printf("Network : %s/%u %s\n", network, prefixlen, net_s);
	printf("Start   : ");
	for (i = 0; i < 15; i += 2) {
		printf("%02x%02x", ip6sb.s6_addr[i], ip6sb.s6_addr[i + 1]);
		if (i < 14)
			printf(":");
	}
	printf("\n");

	printf("End     : ");
	for (i = 0; i < 15; i += 2) {
		printf("%02x%02x", ip6eb.s6_addr[i], ip6eb.s6_addr[i + 1]);
		if (i < 14)
			printf(":");
	}
	printf("\n");
}

int main(int argc, char *argv[])
{
	unsigned short prefixlen;
	char *ptr;

	if (argc < 2) {
		printf("Usage: ipv6-range network/prefix\n");
		exit(EXIT_FAILURE);
	}

	prefixlen = atoi(strchr(argv[1], '/') + 1);
	ptr = strchr(argv[1], '/');
	*ptr = '\0';
	ipv6_range(argv[1], prefixlen);

	exit(EXIT_SUCCESS);
}
