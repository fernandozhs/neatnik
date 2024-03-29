#pragma once

#include "neatnik.hpp"
#include "genotype.hpp"
#include "phenotype.hpp"
#include "species.hpp"


class Organism
{
public:

    // Properties:

    Species* species;

    taxon_group group;

    Genotype* genotype;

    Phenotype* phenotype;

    unsigned int age;

    double score;

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
