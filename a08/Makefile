obj-m		= main.o

K-VERSION	= $(shell uname -r)

all:
		make -C /lib/modules/$(K-VERSION)/build M=$(shell pwd) modules

clean:
		make -C /lib/modules/$(K-VERSION)/build M=$(shell pwd) clean
