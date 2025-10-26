obj-m := gatsby.o

gatsby-obj := gatsby.c gatsby_contents.c

all:
	chmod u+x ./generate_gatsby_contents.sh
	./generate_gatsby_contents.sh
	make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) clean
	rm gatsby_contents.c

