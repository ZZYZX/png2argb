CFLAGS = -std=c99 -s -pedantic -Wall -Wextra -Wfatal-errors -pedantic-errors -O3 -D_XOPEN_SOURCE=500 -D_POSIX_C_SOURCE=200809L
CC     = gcc $(CFLAGS)

all: X11WindowIcon

X11WindowIcon:
	$(CC) -lX11 -o X11WindowIcon X11WindowIcon.c

clean: 
	rm -f X11WindowIcon
