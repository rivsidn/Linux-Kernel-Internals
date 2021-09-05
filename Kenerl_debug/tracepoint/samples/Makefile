obj-m := tracepoint_probe.o
PWD := $(shell pwd)
KVER := $(shell uname -r)
KDIR := /usr/src/linux-headers-`uname -r`

all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	rm -rf *.o *.mod *.mod.c *.mod.o *.ko *.symvers *.order *.a

