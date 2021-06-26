/*
 * mac-to-eui64.c - Generate a modified EUI-64 identifier for the given MAC
 * 		    address.
 *
 * Copyright (C) 2016 - 2017, 2021		Andrew Clayton
 *						<andrew@digital-domain.net>
 *
 * Licensed under the GNU General Public License Version 2 or
 * the GNU Lesser General Public License Version 2.1
 *
 * See GPLv2 & LGPLv2.1 in the source tree.
 */

#include <stdio.h>
#include <stdlib.h>

#include "short_types.h"
#include "common.h"

int main(int argc, char *argv[])
{
	char macstr[20];
	u8 mac[8];
	int i;

	if (argc < 2)
		scanf("%19s", macstr);
	else
		snprintf(macstr, sizeof(macstr), "%s", argv[1]);

	mac_to_eui64(macstr, mac);

	printf("Modified EUI-64 : ");
	for (i = 0; i < 8; i++)
		printf("%02x%s", mac[i], (i < 7) ? ":" : "");
	printf("\n(SLAAC Host)    : ::");
	for (i = 0; i < 8; i += 2)
		printf("%02x%02x%s", mac[i], mac[i + 1], i+1 < 7 ? ":" : "");
	printf("\n(link-local)    : fe80::");
	for (i = 0; i < 8; i += 2)
		printf("%02x%02x%s", mac[i], mac[i + 1], i+1 < 7 ? ":" : "");
	printf("\n");

	exit(EXIT_SUCCESS);
}
