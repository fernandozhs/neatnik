# Makefile for NEATnik.
# Contributors: Fernando Zago.

CFLAGS = -g -Wall -std=c++17
CC = g++

all: build NEATenn; \

debug: build/main.o build/utils.o build/elements.o build/chromosome.o build/genotype.o build/phenotype.o build/organism.o build/group.o build/species.o build/genus.o build/experiment.o build/neatnik.o; \
$(CC) $(CFLAGS) -pg $^ -o NEATenn

NEATenn: build/main.o build/utils.o build/elements.o build/chromosome.o build/genotype.o build/phenotype.o build/organism.o build/group.o build/species.o build/genus.o build/experiment.o build/neatnik.o; \
$(CC) $(CFLAGS) $^ -o $@

build/main.o: main/main.cpp main/main.h; \
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

build/group.o: genus/group.cpp genus/group.h; \
$(CC) $(CFLAGS) -c $< -o $@

build/species.o: genus/species.cpp genus/species.h; \
$(CC) $(CFLAGS) -c $< -o $@

build/genus.o: genus/genus.cpp genus/genus.h; \
$(CC) $(CFLAGS) -c $< -o $@

build/experiment.o: experiment/experiment.cpp experiment/experiment.h; \
$(CC) $(CFLAGS) -c $< -o $@

build/neatnik.o: neatnik/neatnik.cpp neatnik/neatnik.h; \
$(CC) $(CFLAGS) -c $< -o $@

build: ;\
mkdir build

clean: ;\
rm -rf build/ *~
