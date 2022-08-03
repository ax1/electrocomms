# ----------------------------------------------------------------------
# Usage:
#		1. Use Makefile in the algorithm folders to clean and generate libs.
#   2. Then, execute this Makefile.
# ----------------------------------------------------------------------

NAME=electrocomms
RELEASE=-O3
DEBUG=-g3
INCLUDES=-I. -I$(KEM)
CFLAGS=-Wall -Wextra -Wpedantic -Wmissing-prototypes -Wredundant-decls -std=c99 $(INCLUDES) $(EXTRAFLAGS)
KEM=kyber1024
SOURCES=server.c client.c util.c


.PHONY: release debug libs test clean
 
release: libs
	$(CC) $(RELEASE) $(CFLAGS) $(NAME).c $(SOURCES) -L$(KEM) -l$(KEM)_clean -lpthread -o ../bin/$(NAME)

debug: libs
	$(CC) $(DEBUG) $(CFLAGS) $(NAME).c $(SOURCES) -L$(KEM) -l$(KEM)_clean -lpthread -o ../bin/$(NAME)

libs:
	cd $(KEM) && $(MAKE)

test:
	$(CC) $(RELEASE) $(CFLAGS) test.c -L$(KEM) -l$(KEM)_clean -o ../bin/test

clean:
	#$(RM) ../bin/* #Do not remove by now beacuse the keys are currently in that folder
	cd $(KEM) && $(MAKE) clean