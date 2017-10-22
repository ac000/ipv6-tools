/*
 * ipv6-range.c - Given an IPv6 network address with prefix, calculate the
 * 		  range of IPs available.
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
#include <stdint.h>		/* UINT64_MAX */
#include <string.h>
#include <arpa/inet.h>

#include "short_types.h"

#define TXT_FMT_BOLD	"\033[1m"
#define TXT_FMT_END	"\033[0m"

#define HIGH_NIBBLE(byte) (((byte) >> 4) & 0x0f)
#define LOW_NIBBLE(byte)  ((byte) & 0x0f)

/*
 * Based on code from https://github.com/peczenyj/IPv6SubnetCalc/
 */
static void ipv6_range(const char *network, u8 prefixlen)
{
	struct in6_addr ip6b;
	struct in6_addr ip6eb;
	struct in6_addr ip6sb;
	int i;
	int imask = 128 - prefixlen;
	u64 networks = UINT64_MAX;
	char net_s[60] = "\0";
	char *txtfmt = "";

	inet_pton(AF_INET6, network, &ip6b);

	for (i = 15; i >= 0; i--) {
		int j = (imask > 8) ? 8 : imask;
		unsigned char x = (1 << j) - 1;

		ip6sb.s6_addr[i] = ip6b.s6_addr[i] & ~x;
		ip6eb.s6_addr[i] = ip6b.s6_addr[i] | x;
		imask -= j;
	}

	/*
	 * For a prefix length of < 56, calculate the number of /56 and
	 * /64 networks the given network provides. E.g a /48 provides
	 * 256 /56 and 65536 /64 networks.
	 *
	 * For a prefix length of < 64, just display the number of /64s.
	 */
	if (prefixlen < 56)
		snprintf(net_s, sizeof(net_s), "(%llu /56 networks, "
				"%zu /64 networks)", 1LLU << (56 - prefixlen),
				(networks >> prefixlen) + 1);
	else if (prefixlen < 64)
		snprintf(net_s, sizeof(net_s), "(%zu /64 networks)",
				(networks >> prefixlen) + 1);

	printf("Network : %s/%u %s\n", network, prefixlen, net_s);
	printf("Start   : ");
	for (i = 0; i < 15; i += 2) {
		if ((i*8) + 4 > prefixlen)
			txtfmt = TXT_FMT_BOLD;
		printf("%s%x", txtfmt, HIGH_NIBBLE(ip6sb.s6_addr[i]));
		if ((i*8) + 8 > prefixlen)
			txtfmt = TXT_FMT_BOLD;
		printf("%s%x", txtfmt, LOW_NIBBLE(ip6sb.s6_addr[i]));
		if (((i+1) * 8) + 4 > prefixlen)
			txtfmt = TXT_FMT_BOLD;
		printf("%s%x", txtfmt, HIGH_NIBBLE(ip6sb.s6_addr[i + 1]));
		if (((i+1) * 8) + 8 > prefixlen)
			txtfmt = TXT_FMT_BOLD;
		printf("%s%x", txtfmt, LOW_NIBBLE(ip6sb.s6_addr[i + 1]));

		if (i < 14)
			printf(":");
	}
	printf(TXT_FMT_END"\n");
	txtfmt = "";

	printf("End     : ");
	for (i = 0; i < 15; i += 2) {
		if ((i*8) + 4 > prefixlen)
			txtfmt = TXT_FMT_BOLD;
		printf("%s%x", txtfmt, HIGH_NIBBLE(ip6eb.s6_addr[i]));
		if ((i*8) + 8 > prefixlen)
			txtfmt = TXT_FMT_BOLD;
		printf("%s%x", txtfmt, LOW_NIBBLE(ip6eb.s6_addr[i]));
		if (((i+1) * 8) + 4 > prefixlen)
			txtfmt = TXT_FMT_BOLD;
		printf("%s%x", txtfmt, HIGH_NIBBLE(ip6eb.s6_addr[i + 1]));
		if (((i+1) * 8) + 8 > prefixlen)
			txtfmt = TXT_FMT_BOLD;
		printf("%s%x", txtfmt, LOW_NIBBLE(ip6eb.s6_addr[i + 1]));
		if (i < 14)
			printf(":");
	}
	printf(TXT_FMT_END"\n");
}

int main(int argc, char *argv[])
{
	u8 prefixlen;
	char *ptr;

	if (argc < 2 || !strstr(argv[1], "::/")) {
		printf("Usage: ipv6-range network/prefix\n");
		exit(EXIT_FAILURE);
	}

	prefixlen = atoi(strchr(argv[1], '/') + 1);
	ptr = strchr(argv[1], '/');
	*ptr = '\0';
	ipv6_range(argv[1], prefixlen);

	printf("\nA /64 provides 18,446,744,073,709,551,616 addresses\n");

	exit(EXIT_SUCCESS);
}
