CC=gcc
CFLAGS=-lgmp -I.
DEPS = bflib.h
OBJ= main.o bflib.o

%.o: %.c $(DEPS)
	@-$(CC) -c -o $@ $< 

all: $(OBJ)
	@-$(CC) -o $@ $^ $(CFLAGS)
