/*
 * ipv6-gen-slaac.c	- Given an IPv6 network & MAC address create the
 *			  corresponding SLAAC address.
 *
 * Copyright (C) 2017, 2021	Andrew Clayton <andrew@digital-domain.net>
 *
 * Licensed under the GNU General Public License Version 2 or
 * the GNU Lesser General Public License Version 2.1
 *
 * See GPLv2 & LGPLv2.1 in the source tree.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#include "short_types.h"
#include "common.h"

int main(int argc, char *argv[])
{
	int i = 0;
	u8 mac[8];
	u8 slaacn[sizeof(struct in6_addr)];
	char slaac[INET6_ADDRSTRLEN];
	char *ptr;

	if (argc < 2) {
		fprintf(stderr, "Usage: ipv6-gen-slaac <IPv6 network> <MAC address>\n");
		exit(EXIT_FAILURE);
	}

	snprintf(slaac, sizeof(slaac), "%s", argv[1]);
	/* Handle networks specified with a prefixlen e.g 2001:db8::/32 */
	ptr = strchr(slaac, '/');
	if (ptr)
		*ptr = '\0';

	ptr = slaac;
	while ((ptr = strchr(ptr, ':'))) {
		ptr++;
		i++;
	}
	/* Handle networks like 2001:db8:a:b:: */
	if (i > 4)
		slaac[strlen(slaac)-1] = '\0';

	mac_to_eui64(argv[2], mac);

	for (i = 0; i < 8; i += 2)
		snprintf(slaac + strlen(slaac), sizeof(slaac), "%02x%02x%s",
				mac[i], mac[i+1], i+1 < 7 ? ":" : "");

	/* Display in compressed form */
	inet_pton(AF_INET6, slaac, slaacn);
	inet_ntop(AF_INET6, slaacn, slaac, INET6_ADDRSTRLEN);
	printf("SLAAC : %s\n", slaac);

	exit(EXIT_SUCCESS);
}
