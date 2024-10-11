/*
 * ipv6-range.c - Given an IPv6 network address with prefix, calculate the
 * 		  range of IPs available.
 *
 *  Copyright (C) 2015 - 2017, 2020 - 2023	Andrew Clayton
 *						<andrew@digital-domain.net>
 *
 *  Licensed under the GNU General Public License Version 2 or
 *  the GNU Lesser General Public License Version 2.1
 *
 *  See GPLv2 & LGPLv2.1 in the source tree.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>		/* UINT64_MAX */
#include <inttypes.h>
#include <string.h>
#include <arpa/inet.h>

#include "common.h"
#include "short_types.h"

#define HIGH_NIBBLE(byte) (((byte) >> 4) & 0x0f)
#define LOW_NIBBLE(byte)  ((byte) & 0x0f)

static void pretty_print_address(const struct in6_addr *in6, u8 prefixlen)
{
	const char *txtfmt = "";

	for (int i = 0; i < 15; i += 2) {
		if ((i*8) + 4 > prefixlen)
			txtfmt = TXT_FMT_BOLD;
		printf("%s%x", txtfmt, HIGH_NIBBLE(in6->s6_addr[i]));
		if ((i*8) + 8 > prefixlen)
			txtfmt = TXT_FMT_BOLD;
		printf("%s%x", txtfmt, LOW_NIBBLE(in6->s6_addr[i]));
		if (((i+1) * 8) + 4 > prefixlen)
			txtfmt = TXT_FMT_BOLD;
		printf("%s%x", txtfmt, HIGH_NIBBLE(in6->s6_addr[i + 1]));
		if (((i+1) * 8) + 8 > prefixlen)
			txtfmt = TXT_FMT_BOLD;
		printf("%s%x", txtfmt, LOW_NIBBLE(in6->s6_addr[i + 1]));

		if (i < 14)
			printf(":");
	}
	printf(TXT_FMT_END"\n");
}

static void print_nr_nets(u8 prefixlen)
{
	int len = 0;
	char net_s[128] = "\0";

	if (prefixlen >= 64)
		return;

	/*
	 * For a prefix length of < 64, calculate where appropriate the
	 * number of /48, /56, /60 and /64 networks the given network
	 * provides. E.g a /48 provides
	 *
	 *    256 /56s, 4096 /60s and 65536 /64s
	 */
	if (prefixlen < 48)
		len += sprintf(net_s, "%llu /48s, ", 1LLU << (48 - prefixlen));
	if (prefixlen < 56)
		len += sprintf(net_s + len, "%llu /56s, ",
			       1LLU << (56 - prefixlen));
	if (prefixlen < 60)
		len += sprintf(net_s + len,"%llu /60s, ",
			       1LLU << (60 - prefixlen));
	if (prefixlen == 0)
		len += sprintf(net_s + len, "18446744073709551616 /64s, ");
	else if (prefixlen < 64)
		len += sprintf(net_s + len, "%"PRIu64" /64s, ",
				((u64)UINT64_MAX >> prefixlen) + 1);

	net_s[len - 2] = '\0';

	printf("\t  (%s)\n", net_s);
}

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

	inet_pton(AF_INET6, network, &ip6b);

	for (i = 15; i >= 0; i--) {
		int j = (imask > 8) ? 8 : imask;
		u8 x = (1 << j) - 1;

		ip6sb.s6_addr[i] = ip6b.s6_addr[i] & ~x;
		ip6eb.s6_addr[i] = ip6b.s6_addr[i] | x;
		imask -= j;
	}

	printf("Network : %s/%u\n", network, prefixlen);
	print_nr_nets(prefixlen);
	printf("Start   : ");
	pretty_print_address(&ip6sb, prefixlen);
	printf("End     : ");
	pretty_print_address(&ip6eb, prefixlen);
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
