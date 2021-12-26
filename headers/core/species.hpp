/*
  Contributors: Fernando Zago.
*/

#pragma once

#include <unordered_map>
#include <vector>
#include <algorithm>
#include "neatnik.hpp"
#include "utilities.hpp"
#include "organism.hpp"
#include "genus.hpp"
#include "parameters.hpp"
#include "experiment.hpp"


class Species
{
public:

    // Properties:

    Genus* genus;

    taxon_group group;

    std::unordered_map<int, std::vector<Organism*>> organisms;

    double rank = -1.;


    // Constructors:

    Species(Genus* genus_, taxon_group group_, std::vector<Graph> graphs_);

    Species(Genus* genus_, taxon_group group_, Organism* organism_);


    // Destructor:

    ~Species();


    // Methods:

    unsigned int size(const std::vector<int> groups_ = {0, 1});

    typename std::vector<Organism*>::iterator begin(int group_);

    typename std::vector<Organism*>::iterator end(int group_);

    Organism* front(int group_);

    Organism* back(int group_);

    Organism* insert(Organism* organism_);

    Organism* remove(Organism* organism_);

    void purge(Organism* thatOrganism_);

    void purge(const std::vector<int> groups_ = {0, 1});

    void toggle(Organism* organism_, int group_);

    Organism* random(const std::vector<int> groups_ = {0, 1}, const std::vector<double> weights_ = {});

    std::vector<Organism*> retrieve(const std::vector<int> groups_ = {0, 1});

    std::vector<Organism*> sort(const std::vector<int> groups_ = {0, 1});

    void select();

    Organism* spawn();

    bool organism_compatibility(Organism* organism_);

    static bool organism_comparison(Organism* first_organism_, Organism* second_organism_);
};
