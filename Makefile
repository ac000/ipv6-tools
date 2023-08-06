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

.ONESHELL:

.PHONY: all
all: common.o $(elfs)

common.o: common.c common.h
	@echo "  CC     $@"
	$(CC) $(CFLAGS) -c $<

%: %.c
	@echo "  CCLNK  $@"
	@if [ "$@" == "gen-ula" ]; then LIBS="$(LIBS_FOR_GEN_ULA)"; else LIBS=; fi
	@if [ "$@" == "ipv6-gen-slaac" ] || [ "$@" == "mac-to-eui64" ]; then OBJS="common.o"; else OBJS=; fi
	$(CC) $(CFLAGS) -o $@ $$OBJS $$LIBS $<

clean:
	rm -f $(elfs) *.o
