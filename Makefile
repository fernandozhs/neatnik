CFLAGS = -g -Wall -std=c++17
CC = g++ 

all: build experiment

debug: build/neatnik.o build/utils.o build/elements.o build/chromosome.o build/genotype.o build/phenotype.o build/organism.o build/population.o
	$(CC) $(CFLAGS) -pg $^ -o experiment

experiment: build/neatnik.o build/utils.o build/elements.o build/chromosome.o build/genotype.o build/phenotype.o build/organism.o build/population.o
	$(CC) $(CFLAGS) $^ -o $@

build/neatnik.o: neatnik/neatnik.cpp neatnik/neatnik.h
	$(CC) $(CFLAGS) -c $< -o $@

build/utils.o: utils/utils.cpp utils/utils.h
	$(CC) $(CFLAGS) -c $< -o $@

build/elements.o: elements/elements.cpp elements/elements.h
	$(CC) $(CFLAGS) -c $< -o $@

build/chromosome.o: genotype/chromosome.cpp genotype/chromosome.h
	$(CC) $(CFLAGS) -c $< -o $@

build/genotype.o: genotype/genotype.cpp genotype/genotype.h
	$(CC) $(CFLAGS) -c $< -o $@

build/phenotype.o: phenotype/phenotype.cpp phenotype/phenotype.h
	$(CC) $(CFLAGS) -c $< -o $@

build/organism.o: organism/organism.cpp organism/organism.h
	$(CC) $(CFLAGS) -c $< -o $@

build/population.o: population/population.cpp population/population.h
	$(CC) $(CFLAGS) -c $< -o $@

build:
	mkdir build

clean:
	rm -rf build/ *~