all: compile exec

compile:
	g++ -g output.cpp ../Structures/CipherBit.cpp ../Structures/Cipher2Bit.cpp ../Structures/Cipher3Bit.cpp -march=native -O3 -std=c++11 -pthread -I../SEAL -I..SEAL/seal/util/ -L../bin -lseal -o test

exec:
	./test
