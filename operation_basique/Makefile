all: compile exec

compile:
	g++ -g operation_basique.cpp -march=native -O3 -std=c++11 -pthread -I../SEAL -I..SEAL/seal/util/ -L../bin -lseal -o operation_basique

exec:
	./operation_basique
