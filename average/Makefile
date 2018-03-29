all: compile exec

compile:
	g++ -g average_no_weights.cpp -march=native -O3 -std=c++11 -pthread -I../SEAL -I..SEAL/seal/util/ -L../bin -lseal -o average

exec:
	./average
