/*
  Contributors: Fernando Zago and Ingrid Gendron.
*/

#pragma once

#include <cstdint>
#include <stdexcept>
#include <unordered_map>
#include <vector>
#include <utility>
#include <algorithm>
#include "neatnik.hpp"
#include "utilities.hpp"
#include "genotype.hpp"
#include "organism.hpp"
#include "species.hpp"
#include "parameters.hpp"
#include "experiment.hpp"


class Genus
{
public:

    // Properties:

    Experiment* experiment;

    std::unordered_map<Key, std::uint32_t, Hash> logbook;

    std::uint32_t tag_counter = 0;

    std::unordered_map<int, std::vector<Species*>> species;

    std::vector<Organism*> offsprings;


    // Constructor:

    Genus(Experiment* experiment_, std::vector<GenotypeData> genotypes_data_);

    Genus(Experiment* experiment_, GenusData data_);


    // Destructor:

    ~Genus();


    // Methods:

    std::pair<Key, std::uint32_t> tag(unsigned int role_, element_type type_, std::uint32_t source_tag_, std::uint32_t target_tag_);

    std::pair<Key, std::uint32_t> log(Key key_);

    unsigned int size(const std::vector<int> groups_ = {0, 1});

    typename std::vector<Species*>::iterator begin(int group_);

    typename std::vector<Species*>::iterator end(int group_);

    Species* front(int group_);

    Species* back(int group_);

    Species* insert(Species* species_);

    Species* remove(Species* species_);

    void purge(Species* species_);

    void purge(const std::vector<int> groups_ = {0, 1});

    void toggle(Species* species_, int group_);

    Species* random(const std::vector<int> groups_ = {0, 1}, const std::vector<double> weights_ = {});

    std::vector<Species*> retrieve(const std::vector<int> groups_ = {0, 1});

    std::vector<Species*> sort(const std::vector<int> groups_ = {0, 1});

    void select();

    void spawn();

    void speciate();

    bool species_rejection(Species* species_);

    static bool species_comparison(Species* first_pecies_, Species* second_species_);

    GenusData data();
};
