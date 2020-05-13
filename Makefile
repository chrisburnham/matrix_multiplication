#
# Makefile for matrix multiply
#

CXX=g++
CXXFLAGS=-c -Wall -pthread -D_XOPEN_SOURCE=600 -O2 -I../spica/C
LD=g++
LDFLAGS=-pthread
SOURCES=main.c \
        matrix_multiply.cpp
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=MatrixMultiply

%.o:	%.c
	$(CC) $(CFLAGS) $< -o $@

$(EXECUTABLE):	$(OBJECTS)
	$(LD) $(LDFLAGS) $(OBJECTS) -L../spica/C -lSpicaC -o $@

# File Dependencies
###################

main.o:	main.cpp matrix_multiply.h

matrix_multiply.o:	matrix_multiply.cpp matrix_multiply.h


# Additional Rules
##################
clean:
	rm -f *.o *.bc *.s *.ll *~ $(EXECUTABLE) create_square_matrix
