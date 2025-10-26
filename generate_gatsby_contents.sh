#!/bin/bash

echo -n "const char * text = " >gatsby_contents.c
cat book.txt | sed -E 's/"/\\"/g' | awk '{printf("\"%s\\n\"\n", $0)}' | head -c -1 >>gatsby_contents.c
echo -en ";\n\n const unsigned int text_length = $(wc -c book.txt | awk '{print $1}');\n" >>gatsby_contents.c
