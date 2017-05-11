SHELL		= /bin/sh

CC		= gcc
CFLAGS		= -Wall -Wextra -std=c99 -g -O2
LIBS		=

GLIBC_MAJOR	:= $(shell ldd --version | grep -Eo '[0-9]+\.[0-9]+' | \
			   cut -d . -f 1)
GLIBC_MINOR	:= $(shell ldd --version | grep -Eo '[0-9]+\.[0-9]+' | \
			   cut -d . -f 2)
GLIBC_VER_OK	:= $(shell test $(GLIBC_MAJOR) -ge 2 && \
			   test $(GLIBC_MINOR) -ge 17 && \
			   echo 1)

ifneq "$(GLIBC_VER_OK)" "1"
	# clock_* functions need linking against -lrt in glibc < 2.17
	LIBS := -lrt
endif

all: ipv6-range ipv6-arpa ipv6-isin gen-ula mac-to-eui64 mac-type \
	ipv6-extract-mac prefix-to-mask mask-to-prefix ipv6-fmt ipv6-gen-slaac

ipv6-range: ipv6-range.c
	$(CC) $(CFLAGS) -o $@ $<

ipv6-arpa: ipv6-arpa.c
	$(CC) $(CFLAGS) -o $@ $<

ipv6-isin: ipv6-isin.c
	$(CC) $(CFLAGS) -o $@ $<

gen-ula: gen-ula.c
	$(CC) $(CFLAGS) -o $@ $< -luuid -lmhash $(LIBS)

mac-to-eui64: mac-to-eui64.c
	$(CC) $(CFLAGS) -o $@ $<

mac-type: mac-type.c
	$(CC) $(CFLAGS) -o $@ $<

ipv6-extract-mac: ipv6-extract-mac.c
	$(CC) $(CFLAGS) -o $@ $<

prefix-to-mask: prefix-to-mask.c
	$(CC) $(CFLAGS) -o $@ $<

mask-to-prefix: mask-to-prefix.c
	$(CC) $(CFLAGS) -o $@ $<

ipv6-fmt: ipv6-fmt.c
	$(CC) $(CFLAGS) -o $@ $<

ipv6-gen-slaac: ipv6-gen-slaac.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f ipv6-range ipv6-arpa ipv6-isin gen-ula mac-to-eui64 mac-type \
	ipv6-extract-mac prefix-to-mask mask-to-prefix ipv6-fmt ipv6-gen-slaac
