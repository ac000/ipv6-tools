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

LIBS_FOR_GEN_ULA = -luuid -lmhash

ifneq "$(GLIBC_VER_OK)" "1"
	# clock_* functions need linking against -lrt in glibc < 2.17
	LIBS := -lrt
endif

srctmp  = $(wildcard *.c)
sources = $(filter-out common.c,$(srctmp))
elfs    = $(patsubst %.c,%,$(sources))

v = @
ifeq ($V,1)
        v =
endif

.PHONY: all
all: common.o $(elfs)

common.o: common.c common.h
	@echo "  CC     $@"
	$(v)$(CC) $(CFLAGS) -c $<

gen-ula: gen-ula.c
	@echo "  CCLNK  $@"
	$(v)$(CC) $(CFLAGS) -o $@ $< -luuid -lmhash

ipv6-gen-slaac: ipv6-gen-slaac.c common.o
	@echo "  CCLNK  $@"
	$(v)$(CC) $(CFLAGS) -o $@ $< common.o

mac-to-eui64: mac-to-eui64.c common.o
	@echo "  CCLNK  $@"
	$(v)$(CC) $(CFLAGS) -o $@ $< common.o

%: %.c
	@echo "  CCLNK  $@"
	$(v)$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(elfs) *.o
