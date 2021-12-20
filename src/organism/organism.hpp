#pragma once

#include "../neatnik/neatnik.hpp"
#include "../genotype/genotype.hpp"
#include "../phenotype/phenotype.hpp"
#include "../genus/species.hpp"

class Organism
{
public:

    // Properties:

    Species* species;

    taxon_group group;

    Genotype* genotype;

    Phenotype* phenotype;

    unsigned int age;

    std::vector<double> scores;

    std::vector<double> behavior;


    // Constructors:

    Organism(Species* species_, Graph graph_);

    Organism(Organism* organism_);

    Organism(Graph graph_);


    // Destructor:

    ~Organism();


    // Methods:

    Organism* mutate();

    Organism* assimilate(Organism* organism_);

    std::vector<std::vector<std::vector<double>>> react();

    std::vector<std::vector<std::vector<double>>> react(std::vector<std::vector<std::vector<double>>> stimuli_);

    Graph graph() const;
};
