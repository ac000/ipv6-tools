CC=gcc
CFLAGS=-Wall -std=c99 -g -O2

all: ipv6-range ipv6-arpa

ipv6-range: ipv6-range.c
	$(CC) $(CFLAGS) -o ipv6-range ipv6-range.c

ipv6-arpa: ipv6-arpa.c
	$(CC) $(CFLAGS) -o ipv6-arpa ipv6-arpa.c

clean:
	rm -f ipv6-range ipv6-arpa
