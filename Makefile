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

sources = $(wildcard *.c)

.ONESHELL:

.PHONY: all
all: $(patsubst %.c,%,$(sources))
%: %.c
	@echo -e "  CCLNK\t$@"
	@if [[ "$@" == "gen-ula" ]]; then libs="-luuid -lmhash"; fi
	$(CC) $(CFLAGS) -o $@ $$libs $<

clean:
	rm -f $(patsubst %.c,%,$(sources))
