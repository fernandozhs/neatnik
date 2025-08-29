#pragma once

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <cmath>
#include <algorithm>
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

    Organism(Species* species_, GenotypeData genotype_data_);

    Organism(Species* species_, OrganismData data_);

    Organism(Organism* organism_);

    Organism(OrganismData data_);


    // Destructor:

    ~Organism();


    // Methods:

    Organism* mutate();

    Organism* assimilate(Organism* organism_);

    pybind11::array_t<double> react();

    pybind11::array_t<double> react(pybind11::array_t<double> stimuli_);

    OrganismData data() const;
};
