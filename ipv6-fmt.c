/*
 * ipv6-fmt.c - Format an IPv6 address in both compressed & expanded forms.
 *
 *  Copyright (C) 2017		Andrew Clayton <andrew@digital-domain.net>
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

static void fmt_ipv6(const char *addr)
{
	int i;
	u8 addrn[sizeof(struct in6_addr)];
	char addrp[INET6_ADDRSTRLEN];

	inet_pton(AF_INET6, addr, addrn);
	inet_ntop(AF_INET6, addrn, addrp, INET6_ADDRSTRLEN);

	printf("Compressed  : %s\n", addrp);

	printf("Expanded    : ");
	for (i = 0; i < 15; i += 2) {
		printf("%02x%02x", addrn[i], addrn[i + 1]);
		if (i < 14)
			printf(":");
	}
	printf("\n");

	printf("URI Literal : [%s]\n", addrp);
}

int main(int argc, char *argv[])
{
	if (argc < 2) {
		printf("Usage: ipv6-fmt <address>\n");
		exit(EXIT_FAILURE);
	}

	fmt_ipv6(argv[1]);

	exit(EXIT_SUCCESS);
}
