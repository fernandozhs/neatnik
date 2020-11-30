/*
  An `Experiment` drives the evolution of a `Genus`.

  Data:
  ----
  genus: the `Genus*` to be evolved by this `Experiment`.

  Methods:
  -------
  status: prints this `Experiment`'s status.
  evolve: evolves this `Experiment`'s `Genus`.
  evaluate: evaluates the performance of the this `Experiment`'s `Genus`.
  performance: scores the performance of the input `Phenotype`.
*/

/*
  Contributors: Fernando Zago.
*/

#pragma once

#include <vector>
#include <algorithm>
#include "../main/main.h"
#include "../phenotype/phenotype.h"
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

    // Initializes this `Experiment`.
    Experiment(Genus* thatGenus_);


    // Methods:

    // Prints this `Experiment`'s status.
    void status(int cycle_);

    // Evolves this `Experiment`'s `Genus`.
    void evolve(int cycles_ = generational_cycles, bool verbose_ = true);

    // Evaluates the performance of this `Experiment`'s `Genus`.
    void evaluate();

    // Scores the performance of the input `Phenotype`.
    virtual double performance(Phenotype* thatPhenotype_);
};
