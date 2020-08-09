/*
  A `Population` stores a collection of `Organism`s and manages their evolution.

  Data:
  ----
  organisms: a `std::vector<Organism*>` listing all individuals which make up this `Population`.
  history: a `std::vector<Innovation*>` recording this `Population`'s genetic history.
  innovation_counter: an `integer` which keeps track of how many unique `Innovation`s have been recorded.

  Constructors:
  ------------
  initialization: constructs a `Population` composed of `Organisms` characterized by minimal fully-connected `Genotype`s.

  Methods:
  -------
  tag: tags a `Link` or `Node` with a new or existent `Innovation`.
  log: logs a new `Innovation`.
*/

#pragma once

#include <vector>
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
    std::vector<Innovation*> history;

    // A counter storing the identification tag which was last assigned to an `Innovation`.
    int innovation_counter = 0;


public:

    // Constructor:

    // Initialization from an `Archetype`.
    Population(std::vector<Archetype> thoseArchetypes_);


    // Methods:

    // Tags a `Link` or `Node` with a new or existent `Innovation`.
    Innovation* tag(element_type type_, int in_tag_, int out_tag_);

    // Logs a new `Innovation`.
    Innovation* log(element_type type_, int in_tag_, int out_tag_);
};
