CC=gcc

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

