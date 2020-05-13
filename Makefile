#
# Makefile for the CIS-4230 Linear Equations project.
#

CC=gcc
CFLAGS=-c -Wall -pthread -std=c99 -D_XOPEN_SOURCE=600 -O2 -I../spica/C
LD=gcc
LDFLAGS=-pthread
SOURCES=main.c \
        matrix_multiply.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=MatrixMultiply

%.o:	%.c
	$(CC) $(CFLAGS) $< -o $@

$(EXECUTABLE):	$(OBJECTS)
	$(LD) $(LDFLAGS) $(OBJECTS) -L../spica/C -lSpicaC -o $@

# File Dependencies
###################

main.o:	main.c matrix_multiply.h

matrix_multiply.o:	matrix_multiply.c matrix_multiply.h


# Additional Rules
##################
clean:
	rm -f *.o *.bc *.s *.ll *~ $(EXECUTABLE) create_square_matrix
