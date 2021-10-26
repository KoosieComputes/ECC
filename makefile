all: main.cpp domainparameters.cpp bflib.c
	g++ -g -O2 -std=c++11 -pthread -o all main.cpp domainparameters.cpp -lntl -lgmp -lm

