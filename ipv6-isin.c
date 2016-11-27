/*
 * ipv6-isin.c - Given an IPv6 network/prefix and an IPv6 address, determine
 * 		 if the address falls within the given network.
 *
 *  Copyright (C) 2015	Andrew Clayton <andrew@digital-domain.net>
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

/*
 * Function based on the tcp wrappers IPv6 code from
 * Casper Dik (Casper.Dik@Holland.Sun.COM)
 */
static void ipv6_isin(const char *network, unsigned short prefixlen,
		      const char *address)
{
	unsigned char ip6b[sizeof(struct in6_addr)];
	unsigned char *p = ip6b;
	char ip6s[INET6_ADDRSTRLEN];

	inet_pton(AF_INET6, address, ip6b);

	p += prefixlen / 8;
	prefixlen %= 8;

	if (prefixlen !=  0)
		*p &= 0xff << (8 - prefixlen);

	while (p < ip6b + sizeof(ip6b))
		*p++ = 0;

	inet_ntop(AF_INET6, ip6b, ip6s, INET6_ADDRSTRLEN);
	if (strcmp(network, ip6s) == 0)
		printf("Yes\n");
	else
		printf("No\n");
}

int main(int argc, char *argv[])
{
	unsigned short prefixlen;
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
