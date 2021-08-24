CC=gcc
CFLAGS=-lgmp -I.
DEPS = bflib.h
OBJ= main.o bflib.o curve.o

%.o: %.c $(DEPS)
	@-$(CC) -c -o $@ $< 

all: $(OBJ)
	@-$(CC) -o $@ $^ $(CFLAGS)
