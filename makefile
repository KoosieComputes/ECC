all: main.cpp bflib.c
	g++ -g -O2 -std=c++11 -pthread -o all main.cpp -lntl -lgmp -lm

