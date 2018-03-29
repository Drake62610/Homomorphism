all: compile exec

compile:
	#g++ -g comparaison-1_bit.cpp -march=native -O3 -std=c++11 -pthread -I../SEAL -I..SEAL/seal/util/ -L../bin -lseal -o comparaison
	g++ -g testvector.cpp -march=native -O3 -std=c++11 -pthread -I../SEAL -I..SEAL/seal/util/ -L../bin -lseal -o comparaison
exec:
	./comparaison
