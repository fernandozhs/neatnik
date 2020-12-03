# Makefile for Neatnik.
# Contributors: Fernando Zago.

CFLAGS = -g -Wall -std=c++17
CC = g++

all: build Neatnik; \

debug: build/main.o build/io.o build/utils.o build/elements.o build/chromosome.o build/genotype.o build/phenotype.o build/organism.o build/species.o build/experiment.o build/xor.o build/genus.o; \
$(CC) $(CFLAGS) -pg $^ -o NEATenn

Neatnik: build/main.o build/io.o build/utils.o build/elements.o build/chromosome.o build/genotype.o build/phenotype.o build/organism.o build/species.o build/experiment.o build/xor.o build/genus.o; \
$(CC) $(CFLAGS) $^ -o $@

build/main.o: main/main.cpp main/main.h; \
$(CC) $(CFLAGS) -c $< -o $@

build/io.o: io/io.cpp io/io.h; \
$(CC) $(CFLAGS) -c $< -o $@

build/utils.o: utils/utils.cpp utils/utils.h; \
$(CC) $(CFLAGS) -c $< -o $@

build/elements.o: elements/elements.cpp elements/elements.h; \
$(CC) $(CFLAGS) -c $< -o $@

build/chromosome.o: genotype/chromosome.cpp genotype/chromosome.h; \
$(CC) $(CFLAGS) -c $< -o $@

build/genotype.o: genotype/genotype.cpp genotype/genotype.h; \
$(CC) $(CFLAGS) -c $< -o $@

build/phenotype.o: phenotype/phenotype.cpp phenotype/phenotype.h; \
$(CC) $(CFLAGS) -c $< -o $@

build/organism.o: organism/organism.cpp organism/organism.h; \
$(CC) $(CFLAGS) -c $< -o $@

build/species.o: genus/species.cpp genus/species.h; \
$(CC) $(CFLAGS) -c $< -o $@

build/experiment.o: experiment/experiment.cpp experiment/experiment.h; \
$(CC) $(CFLAGS) -c $< -o $@

build/xor.o: experiment/xor.cpp experiment/xor.h; \
$(CC) $(CFLAGS) -c $< -o $@

build/genus.o: genus/genus.cpp genus/genus.h; \
$(CC) $(CFLAGS) -c $< -o $@

build: ;\
mkdir build

clean: ;\
rm -rf build/ *~
