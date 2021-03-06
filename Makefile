# Makefile for png2argb

CFLAGS = -std=c99 -s -pedantic -Wall -Wextra -Wfatal-errors -pedantic-errors -O3 -D_XOPEN_SOURCE=500 -D_POSIX_C_SOURCE=200809L
CC     = gcc $(CFLAGS)

LIBPNG_DIR=/usr/local
LIBPNG_INCDIR=$(LIBPNG_DIR)/include
LIBPNG_LIBDIR=$(LIBPNG_DIR)/lib

all: png2argb.c
	$(CC) -o png2argb png2argb.c -lpng -L$(LIBPNG_LIBDIR) -I$(LIBPNG_INCDIR)

install:
	cp -v png2argb /usr/local/bin

uninstall:
	rm -f /usr/local/bin/png2argb

clean: 
	rm -f png2argb
