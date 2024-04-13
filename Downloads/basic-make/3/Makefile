# ***Do not modify any recipes!***

.PHONY: all
# TODO: This really only needs one prerequisite
all:

.PHONY: clean
# If you have your clean target depend on these files, you're forcing
# Make to create all these files...before deleting them
clean:
	rm -f neko.inc.c nekosay.S nekosay.o nekosay

# TODO: generate a C string literal from the "neko.ascii" ascii art file
neko.inc.c:
	echo "static const char *neko =" > neko.inc.c
	sed -e 's/\\/\\\\/g; s/^\(.*\)$$/"\1\\n"/;' neko.ascii >> neko.inc.c
	echo ";" >> neko.inc.c

# TODO: generate assembly using the nekosay C source
# note that nekosay.c #include's neko.inc.c as a way to get the string:
# DO NOT DELETE THE neko.inc.c PREREQUISITE; it's been provided as a freebie
# for this assignment. You will need to add another file to the prerequisites
nekosay.S: neko.inc.c
	gcc -g -S -o nekosay.S nekosay.c

# TODO: generate object code from the assembly code
nekosay.o:
	as -o nekosay.o nekosay.S

# TODO: link (using gcc) the object code into a binary
nekosay:
	gcc -o nekosay nekosay.o
