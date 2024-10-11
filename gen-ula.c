/*
 * gen-ula.c -	Generate an IPv6 Unique Local Address prefix
 *
 * Copyright (C) 2016		Andrew Clayton <andrew@digital-domain.net>
 *
 * Licensed under the GNU General Public License Version 2 or
 * the GNU Lesser General Public License Version 2.1
 *
 * See GPLv2 & LGPLv2.1 in the source tree.
 */

#define _POSIX_C_SOURCE		199309L	/* clock_gettime(2) */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <uuid/uuid.h>

#include <mhash.h>

#include "short_types.h"

int main(void)
{
	struct timespec tp;
	uuid_t uuid;
	char uuid_s[37];
	char key[128];
	char ula[15] = "fd";		/* fdxx:xxxx:xxxx + \0 */
	u8 *xhash;
	MHASH td;
	int len;
	int i;

	/* Generate an IPv6 ULA prefix based on the algorithm from RFC 4193 */
	uuid_generate(uuid);
	uuid_unparse(uuid, uuid_s);
	clock_gettime(CLOCK_REALTIME, &tp);
	len = sprintf(key, "%s%ld%ld", uuid_s, tp.tv_sec, tp.tv_nsec);

	td = mhash_init(MHASH_SHA1);
	mhash(td, key, len);
	xhash = mhash_end(td);

	len = 2;
	/* Use lower 40 bits (5 bytes) */
	for (i = 19; i > 14; i--) {
		if (!(i & 1)) {
			strcat(ula, ":");
			len++;
		}
		len += sprintf(ula + len, "%.2x", xhash[i]);
	}
	free(xhash);

	printf("%s::/48\n", ula);
	printf("/64 subnet range:\n");
	printf("    %s:0000::/64 -\n", ula);
	printf("    %s:ffff::/64\n", ula);

	exit(EXIT_SUCCESS);
}
