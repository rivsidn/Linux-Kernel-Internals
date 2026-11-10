CC ?= cc
CFLAGS ?= -O2 -Wall -Wextra -Wpedantic

.PHONY: all clean

all: tap_demo

tap_demo: tap_demo.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f tap_demo
