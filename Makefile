SHELL		= /bin/sh

CC		= gcc
CFLAGS		= -Wall -std=c99 -g -O2
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

all: ipv6-range ipv6-arpa ipv6-isin gen-ula mac-to-eui64 mac-type

ipv6-range: ipv6-range.c
	$(CC) $(CFLAGS) -o ipv6-range ipv6-range.c

ipv6-arpa: ipv6-arpa.c
	$(CC) $(CFLAGS) -o ipv6-arpa ipv6-arpa.c

ipv6-isin: ipv6-isin.c
	$(CC) $(CFLAGS) -o ipv6-isin ipv6-isin.c

gen-ula: gen-ula.c
	$(CC) $(CFLAGS) -o gen-ula gen-ula.c -luuid -lmhash $(LIBS)

mac-to-eui64: mac-to-eui64.c
	$(CC) $(CFLAGS) -o mac-to-eui64 mac-to-eui64.c

mac-type: mac-type.c
	$(CC) $(CFLAGS) -o mac-type mac-type.c

clean:
	rm -f ipv6-range ipv6-arpa ipv6-isin gen-ula mac-to-eui64 mac-type
