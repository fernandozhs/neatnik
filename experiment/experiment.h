/*
  An `Experiment` drives the evolution of a `Genus`.

  Data:
  ----
  genus: the `Genus*` to be evolved by this `Experiment`.

  Constructor:
  -----------
  initialization: initializes this `Experiment` by supplying it with a `Genus` to be evolved.

  Destructor:
  ----------
  recursive: deletes this `Experiment` and its associated `Genus`.

  Methods:
  -------
  evolve: evolves this `Experiment`'s `Genus`.
  evaluate: evaluates the performance of the this `Experiment`'s `Genus`.
  performance: scores the performance of the input `Organism`.
*/

/*
  Contributors: Fernando Zago.
*/

#pragma once

#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include "../neatnik/neatnik.h"
#include "../organism/organism.h"
#include "../genus/species.h"
#include "../genus/genus.h"

class Experiment
{
public:

    // Data:

    // The `Genus` to be evolved by this `Experiment`.
    Genus* genus;


    // Constructor:

    // Initializes this `Experiment` by supplying it with a `Genus` to be evolved.
    Experiment(Genus* thatGenus_);


    // Destructor:

    // Recursive destructor responsible for deleting this `Experiment` and its associated `Genus`s.
    virtual ~Experiment();


    // Methods:

    // Evolves this `Experiment`'s `Genus`.
    void evolve(int cycles_ = generational_cycles, bool verbose_ = true);

    // Evaluates the performance of this `Experiment`'s `Genus`.
    void evaluate();

    // Scores the performance of the input `Organism`.
    virtual double performance(Organism* thatOrganism_) = 0;
};
