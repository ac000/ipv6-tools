CC=gcc
CFLAGS=-Wall -std=c99 -g -O2

all: ipv6-range ipv6-arpa ipv6-isin gen-ula

ipv6-range: ipv6-range.c
	$(CC) $(CFLAGS) -o ipv6-range ipv6-range.c

ipv6-arpa: ipv6-arpa.c
	$(CC) $(CFLAGS) -o ipv6-arpa ipv6-arpa.c

ipv6-isin: ipv6-isin.c
	$(CC) $(CFLAGS) -o ipv6-isin ipv6-isin.c

gen-ula: gen-ula.c
	$(CC) $(CFLAGS) -o gen-ula gen-ula.c -luuid -lmhash

clean:
	rm -f ipv6-range ipv6-arpa ipv6-isin gen-ula
