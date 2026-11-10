CC ?= cc
CFLAGS ?= -O2 -Wall -Wextra -Wpedantic

.PHONY: all clean

all: tun_reader

tun_reader: tun_reader.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f tun_reader
