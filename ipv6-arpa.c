/*
 * ipv6-arpa.c - Given an IPv6 address display it in ip6.arpa format.
 *
 *  Copyright (C) 2015	Andrew Clayton <andrew@digital-domain.net>
 *
 *  Licensed under the GNU General Public License Version 2 or
 *  the GNU Lesser General Public License Version 2.1
 *
 *  See GPLv2 & LGPLv2.1 in the source tree.
 */

#define _DEFAULT_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

static void ipv6_arpa(const char *address)
{
	struct in6_addr ip6b;
	int i;
	int len = 0;
	char ips[INET6_ADDRSTRLEN];

	inet_pton(AF_INET6, address, &ip6b);

	for (i = 0; i < 15; i += 2) {
		len += sprintf(ips + len,"%02x%02x", ip6b.s6_addr[i],
				ip6b.s6_addr[i + 1]);
		if (i < 14)
			len += sprintf(ips + len, ":");
	}

	printf("Address  : %s\n", ips);
	printf("ip6.arpa :- \n    ");
	for (i = strlen(ips) - 1; i >= 0; i--) {
		if (ips[i] == ':')
			continue;
		printf("%c.", ips[i]);
	}
	printf("ip6.arpa.\n");
}

int main(int argc, char *argv[])
{
	if (argc < 2) {
		printf("Usage: ipv6-arpa address\n");
		exit(EXIT_FAILURE);
	}

	ipv6_arpa(argv[1]);

	exit(EXIT_SUCCESS);
}
