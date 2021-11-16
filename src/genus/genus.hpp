/*
  A `Genus` stores and manages a collection of `Species`.

  Data:
  ----
  experiment: the `Experiment*` to which this `Genus` is associated.
  tag_counter: an `unsigned integer` which keeps track of the total number of logged `Link`s and `Node`s.
  logbook: an `std::unordered_map<unsigned long int, unsigned int>` logging all `Link`s and `Node`s in this `Genus`.
  species: an `std::unordered_map<int, std::vector<Species*>>` cataloguing all `Species` in this `Genus`.
  organisms: an `std::vector<Organism*>` storing this `Genus`' next generation of `Organisms*`.

  Constructor:
  -----------
  population: populates this `Genus` with `Organism`s initialized from minimal `Graph`s.

  Destructor:
  ----------
  recursive: recursively deletes this `Genus` and all its `Species`.

  Methods:
  -------
  tag: tags a `Link` or `Node` with a new or existing identification tag.
  log: logs a new `Link` or `Node`.
  size: retrieves the total number of stored `Organism`s from the matching group(s).
  begin: retrieves an iterator at the beginning of a given group.
  end: retrieves an iterator at the end of a given group.
  front: retrieves the first `Species*` of a given group.
  back: retrieves the last `Species*` of a given group.
  insert: inserts a `Species*` into this `Genus`.
  remove: removes a `Species*` from this `Genus`.
  purge: purges a `Species*` from this `Genus`.
  toggle: toggles the group associated with the input `Species*`.
  random: selects a random `Species*` from the matching group(s).
  retrieve: retrieves all `Species*` from the matching group(s).
  sort: sorts all `Species*` from the matching group(s) according to their performance.
  select: finds the best performing `Organism`s and purges stagnated `Species`.
  spawn: spawns a new generation of `Organism`s.
  speciate: assigns spawned `Organism`s to a new or existing `Species`.
  species_rejection: the criterion for rejecting a `Species*`.
  species_comparison: the criterion for comparing two `Species*`.
*/

/*
  Contributors: Fernando Zago and Ingrid Gendron.
*/

#pragma once

#include <unordered_map>
#include <vector>
#include <utility>
#include <algorithm>
#include "../neatnik/neatnik.hpp"
#include "../utils/utils.hpp"
#include "../genotype/genotype.hpp"
#include "../organism/organism.hpp"
#include "../genus/species.hpp"
#include "../experiment/parameters.hpp"
#include "../experiment/experiment.hpp"

class Genus
{
public:

    // Data:

    // The `Experiment*` to which this `Genus` is associated.
    Experiment* experiment;

    // A counter storing the identification tag which was last assigned to a `Link` or `Node`.
    unsigned int tag_counter = 0;

    // The log of all `Link`s and `Node`s in this `Genus`.
    std::unordered_map<unsigned long int, unsigned int> logbook;

    // A catalog of `Species*` organized by group.
    std::unordered_map<int, std::vector<Species*>> species;

    // This `Genus`' next generation of `Organism*`s.
    std::vector<Organism*> organisms;


    // Constructor:

    // Constructor responsible for populating this `Genus` with `Organism`s initialized by minimal `Graph`s.
    Genus(Experiment* thatExperiment_, std::vector<Graph> thoseGraphs_);


    // Destructor:

    // Destructor responsible for recursively deleting this `Genus` and all its `Species`.
    ~Genus();


    // Methods:

    // Tags a `Link` or `Node` with a new or existing identification tag.
    std::pair<unsigned long int, unsigned int> tag(int role_, element_type type_, unsigned int in_tag_, unsigned int out_tag_);

    // Logs a new `Link` or `Node`.
    std::pair<unsigned long int, unsigned int> log(unsigned long int key_);

    // Retrieves the total number of stored `Species` from the matching group(s).
    int size(const std::vector<int> groups_ = {0, 1});

    // Retrieves an iterator at the beginning of a given group.
    typename std::vector<Species*>::iterator begin(int group_);

    // Retrieves an iterator at the end of a given group.
    typename std::vector<Species*>::iterator end(int group_);

    // Retrieves the first `Species*` of a given group.
    Species* front(int group_);

    // Retrieves the last `Species*` of a given group.
    Species* back(int group_);

    // Inserts a `Species*` into this `Genus`.
    Species* insert(Species* thatSpecies_);

    // Removes a `Species*` from this `Genus`.
    Species* remove(Species* thatSpecies_);

    // Purges a `Species*` from this `Genus`.
    void purge(Species* thatSpecies_);

    // Purges all `Species*` from the matching group(s).
    void purge(const std::vector<int> groups_ = {0, 1});

    // Toggles the group associated with the input `Species*`.
    void toggle(Species* thatSpecies_, int group_);

    // Selects a random `Species*` from the matching group(s).
    Species* random(const std::vector<int> groups_ = {0, 1}, const std::vector<double> weights_ = {});

    // Retrieves all `Species*` from the matching group(s).
    std::vector<Species*> retrieve(const std::vector<int> groups_ = {0, 1});

    // Sorts all `Species*` from the matching group(s) according to their performance.
    std::vector<Species*> sort(const std::vector<int> groups_ = {0, 1});

    // Finds the best performing `Organism`s and purges stagnated `Species`.
    void select();

    // Spawns a new generation of `Organism`s.
    void spawn();

    // Assigns spawned `Organism`s to a new or existing `Species`.
    void speciate();

    // The criterion for rejecting a `Species*`.
    bool species_rejection(Species* thatSpecies_);

    // The criterion for comparing two `Species*`.
    static bool species_comparison(Species* thatSpecies_, Species* thisSpecies_);
};
