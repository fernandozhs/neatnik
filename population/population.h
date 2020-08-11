/*
  A `Population` stores a collection of `Organism`s and manages their evolution.

  Data:
  ----
  organisms: a `std::vector<Organism*>` listing all individuals which make up this `Population`.
  history: a `std::unordered_map<long int, Innovation*>` logging this `Population`'s genetic history.
  innovation_counter: an `integer` which keeps track of how many unique `Innovation`s have been recorded.

  Constructors:
  ------------
  initialization: initializates this `Population` with `Organism`s characterized by minimal fully-connected `Genotype`s.

  Methods:
  -------
  tag: tags a `Link` or `Node` with a new or existent `Innovation`.
  log: logs a new `Innovation`.
  key: generates an `Innovation`'s unique identification key.
*/

/*
  Contributors: Fernando Zago and Hans Hopkins.
*/

#pragma once

#include <vector>
#include <unordered_map>
#include <fstream>
#include <string>
#include "../neatnik/neatnik.h"
#include "../innovation/innovation.h"
#include "../organism/organism.h"

class Population
{
private:

    // Data:

    // The collection of `Organism*`s which make up this `Population`.
    std::vector<Organism*> organisms;

    // The collection of `Innovation*`s recording this `Population`'s genetic history.
    std::unordered_map<long int, Innovation*> history;

    // A counter storing the identification tag which was last assigned to an `Innovation`.
    unsigned int innovation_counter = 0;


public:

    // Constructor:

    // Initializates this `Population` with `Organism`s characterized by minimal fully-connected `Genotype`s.
    Population(std::vector<Archetype> thoseArchetypes_);


    // Methods:

    // Tags a `Link` or `Node` with a new or existent `Innovation`.
    Innovation* tag(element_type type_, unsigned int in_tag_, unsigned int out_tag_);

    // Logs a new `Innovation`.
    Innovation* log(element_type type_, unsigned int in_tag_, unsigned int out_tag_);

    // Generates an `Innovation`'s unique identification key.
    long int key(element_type type_, unsigned int in_tag_, unsigned int out_tag_);
};
