#!/bin/bash

echo -n "const char * text = " >gatsby_contents.c
cat book.txt | sed -E 's/"/\\"/g' | sed -E 's/(^.*$)/"\1\\n"/g' | head -c -1 >>gatsby_contents.c
echo -en ";\n\n const unsigned int text_length = sizeof(text);\n" >>gatsby_contents.c
