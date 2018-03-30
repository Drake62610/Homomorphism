all: compile exec

compile:
	g++ -g main.cpp ../Structures/CipherInt8bit.cpp -march=native -O3 -std=c++11 -pthread -I../SEAL -I..SEAL/seal/util/ -L../bin -lseal -o main
exec:
	./main
