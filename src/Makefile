# ------------------------------------------------------------
# Usage:
#		1. Use Makefile in the algorithm to clean and generate lib.
#   2. Then, execute this Makefile.
# ------------------------------------------------------------

NAME=main
RELEASE=-O3
DEBUG=-g3
INCLUDES= -I. -I$(KEM)
CFLAGS=-Wall -Wextra -Wpedantic -Wmissing-prototypes -Wredundant-decls -std=c99 $(INCLUDES) $(EXTRAFLAGS)
KEM=kyber1024


.PHONY: release debug clean
 
release:
	$(CC) $(RELEASE) $(CFLAGS)  $(NAME).c -L$(KEM) -l$(KEM)_clean -o ../bin/$(NAME)

debug:
	$(CC) $(DEBUG) $(CFLAGS) $(NAME).c -L$(KEM) -l$(KEM)_clean -o ../bin/$(NAME)

clean:
	$(RM) ./kyber1024/*.o
	$(RM) ./kyber1024/*.a