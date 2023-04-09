/*
 * ipv4mapped-ipv6.c - Given an IPv4 address produce an IPv4-mapped IPv6
 *		       address.
 *
 * Copyright (C) 2023		Andrew Clayton <andrew@digital-domain.net>
 *
 * Licensed under the GNU General Public License Version 2 or
 * the GNU Lesser General Public License Version 2.1
 *
 * See GPLv2 & LGPLv2.1 in the source tree.
 */

#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>

#include "common.h"
#include "short_types.h"

int main(int argc, char *argv[])
{
	struct in_addr addr;
	u32 naddr;

	if (argc < 2) {
		printf("Usage: ipv4mapped-ipv6 <IPv4 addr>\n");
		exit(EXIT_FAILURE);
	}

	inet_pton(AF_INET, argv[1], &addr);
	naddr = htonl(addr.s_addr);

	printf("IPv4-mapped IPv6 : ::ffff:%s%s%s\n",
	       TXT_FMT_BOLD, argv[1], TXT_FMT_END);
	printf("                 : ::ffff:%s%04x:%04x%s\n",
	       TXT_FMT_BOLD, (naddr >> 16) & 0x0000ffff, naddr & 0x0000ffff,
	       TXT_FMT_END);

	exit(EXIT_SUCCESS);
}
