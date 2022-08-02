# ----------------------------------------------------------------------
# Usage:
#		1. Use Makefile in the algorithm folders to clean and generate libs.
#   2. Then, execute this Makefile.
# ----------------------------------------------------------------------

NAME=main
RELEASE=-O3
DEBUG=-g3
INCLUDES= -I. -I$(KEM)
CFLAGS=-Wall -Wextra -Wpedantic -Wmissing-prototypes -Wredundant-decls -std=c99 $(INCLUDES) $(EXTRAFLAGS)
KEM=kyber1024
SOURCES=server.c client.c util.c


.PHONY: release debug clean
 
release:
	$(CC) $(RELEASE) $(CFLAGS) $(NAME).c $(SOURCES) -L$(KEM) -l$(KEM)_clean -lpthread -o ../bin/$(NAME)

debug:
	$(CC) $(DEBUG) $(CFLAGS) $(NAME).c $(SOURCES) -L$(KEM) -l$(KEM)_clean -lpthread -o ../bin/$(NAME)

test:
	$(CC) $(RELEASE) $(CFLAGS) test.c -L$(KEM) -l$(KEM)_clean -o ../bin/test

clean:
	$(RM) ./kyber1024/*.o
	$(RM) ./kyber1024/*.a