all: main.cpp domainparameters.cpp bflib.c curve.c
	g++ -g -O2 -std=c++11 -pthread -o all main.cpp domainparameters.cpp curve.c bflib.c -lntl -lgmp -lm

