.PHONY : all clean

#GIT_VERSION := "$(shell git describe --abbrev=4 --dirty --always --tags)" 
#CFLAGS := -DVERSION='"$(GIT_VERSION)"'

all: advisor 

advisor: main.c tree.o 
	gcc -g -c -Wall -W main.c tree.o -o advisor
	clear

tree.o: tree.c tree.h 
	gcc -c tree.c -o tree.o

clean: 
	rm -f *.o advisor
	clear