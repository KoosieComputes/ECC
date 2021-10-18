all: main.cpp polymod.cpp bflib.c
	g++ -g -O2 -std=c++11 -pthread -o all main.cpp polymod.cpp -lntl -lgmp -lm

