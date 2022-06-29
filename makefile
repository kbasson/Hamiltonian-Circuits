hamiltonianCircuit: hamiltonianCircuit.o helpers.o
	clang -Wall -pedantic -std=c99 hamiltonianCircuit.o helpers.o -o hamiltonianCircuit

hamiltonianCircuit.o: hamiltonianCircuit.c hamiltonianCircuit.h
	clang -Wall -pedantic -std=c99 -c hamiltonianCircuit.c -o hamiltonianCircuit.o

helpers.o: helpers.c hamiltonianCircuit.h
	clang -Wall -pedantic -std=c99 -c helpers.c -o helpers.o

clean:
	rm *.o
