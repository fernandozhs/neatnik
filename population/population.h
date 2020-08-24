/*
  A `Population` stores a collection of `Organism`s and manages their evolution.

  Data:
  ----
  organisms: a `std::vector<Organism*>` listing all individuals which make up this `Population`.
  logbook: a `std::unordered_map<long int, int>` logging all `Link`s and `Node`s in this `Population`.
  innovation_counter: an `integer` which keeps track of the total number of logged `Link`s and `Node`s.

  Constructors:
  ------------
  initialization: initializates this `Population` with `Organism`s characterized by minimal fully-connected `Genotype`s.

  Methods:
  -------
  tag: tags a `Link` or `Node` with a new or existent identification tag.
  log: logs a new `Link` or `Node`.
  key: generates a unique search key for a given `Link` or `Node`.
*/

/*
  Contributors: Fernando Zago and Hans Hopkins.
*/

#pragma once

#include <vector>
#include <utility>
#include <unordered_map>
#include "../neatnik/neatnik.h"
#include "../utils/utils.h"
#include "../organism/organism.h"

class Population
{
private:

    // Data:

    // The collection of `Organism*`s which make up this `Population`.
    std::vector<Organism*> organisms;

    // The log of all `Link`s and `Node`s in this `Population`.
    std::unordered_map<long int, unsigned int> logbook;

    // A counter storing the identification tag which was last assigned to a `Link` or `Node`.
    unsigned int tag_counter = 0;


public:

    // Constructor:

    // Initializates this `Population` with `Organism`s characterized by minimal fully-connected `Genotype`s.
    Population(std::vector<Archetype> thoseArchetypes_);


    // Methods:

    // Tags a `Link` or `Node` with a new or existent identification tag.
    std::pair<long int, unsigned int> tag(int role_, element_type type_, unsigned int in_tag_, unsigned int out_tag_);

    // Logs a new `Link` or `Node`.
    std::pair<long int, unsigned int> log(long int key_);

    // Generates a unique search key for a given `Link` or `Node`.
    long int key(int role_, element_type type_, unsigned int in_tag_, unsigned int out_tag_);
};
