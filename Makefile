obj-m := gatsby.o

gatsby-obj := gatsby.c gatsby_contents.c

all:
	echo -n "const char * text = " >gatsby_contents.c
	cat book.txt | sed -E 's/(^.*$)/"\1\\n"/g'^C | head -c -1 >>gatsby_contents.c
	echo -en ";\n\n const unsigned int text_Length = sizeof(text);\n" >>gatsby_contents.c	
	make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) clean
	rm gatsby_contents.c

