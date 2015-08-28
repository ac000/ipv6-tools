CC=gcc
CFLAGS=-Wall -std=c99 -g -O2

ipv6-range: ipv6-range.c
	$(CC) $(CFLAGS) -o ipv6-range ipv6-range.c

clean:
	rm -f ipv6-range
