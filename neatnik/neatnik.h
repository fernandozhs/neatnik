/*
  `Neatnik` controls a `Genus`' evolution.

  Data:
  ----
  experiment: the `Experiment*` responsible for driving evolution.
  genus: the `Genus*` to undergo evolution.
  tag_counter: an `unsigned integer` which keeps track of the total number of logged `Link`s and `Node`s.

  Constructors:
  ------------
  initialization: initializes `Neatnik`.

  Methods:
  -------
  status: prints a summary of `Neatnik`'s current state.
  tag: tags a `Link` or `Node` with a new or existing identification tag.
  log: logs a new `Link` or `Node`.
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
#include "../genus/genus.h"
#include "../experiment/experiment.h"

class Neatnik
{
public:

    // Data:

    // The `Experiment*` responsible for driving evolution.
    Experiment* experiment;

    // The `Genus*` to undergo evolution.
    Genus* genus;

    // A counter storing the identification tag which was last assigned to a `Link` or `Node`.
    unsigned int element_counter = 0;

    // A counter storing the identification tag which was last assigned to a `Species`.
    unsigned int species_counter = 0;

    // The log of all `Link`s and `Node`s in this `Genus`.
    std::unordered_map<long int, unsigned int> logbook;


    // Constructor:

    // Initializes `Neatnik`.
    Neatnik(Experiment* thatExperiment_, std::vector<Archetype> thoseArchetypes_);


    // Methods:

    // Tags a `Species` with a new identification tag.
    unsigned int tag();

    // Tags a `Link` or `Node` with a new or existing identification tag.
    std::pair<long int, unsigned int> tag(int role_, element_type type_, unsigned int in_tag_, unsigned int out_tag_);

    // Logs a new `Link` or `Node`.
    std::pair<long int, unsigned int> log(long int key_);

    // Evolves the `Genus` through a single generational cycle.
    void evolve();
};
