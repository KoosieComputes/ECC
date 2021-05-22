CC=gcc
CFLAGS=-I.
DEPS = pflib.h
OBJ= main.o pflib.o

%.o: %.c $(DEPS)
	@-$(CC) -c -o $@ $< $(CFLAGS)

all: $(OBJ)
	@-$(CC) -o $@ $^ $(CFLAGS)
