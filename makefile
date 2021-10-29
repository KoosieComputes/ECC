all: main.cpp domainparameters.cpp bflib.c curve.cpp
	g++ -g -O2 -std=c++11 -pthread -o all main.cpp domainparameters.cpp curve.cpp bflib.c -lntl -lgmp -lm

