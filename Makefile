obj-m := gatsby.o

gatsby-objs := gatsby-driver.o gatsby_contents.o

all:
	chmod u+x ./generate_gatsby_contents.sh
	./generate_gatsby_contents.sh
	make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) clean
	rm gatsby_contents.c

