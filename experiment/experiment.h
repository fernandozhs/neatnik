/*
  An `Experiment` drives the evolution of a `Genus`.

  Methods:
  -------
  evaluate: evaluates the performance of a `Genus`, `Species`, or `Organism`.
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

    // Methods:

    // Evaluates the performance of the input `Genus`.
    void evaluate(Genus* thatGenus_);

    // Evaluates the performance of the input `Species`.
    void evaluate(Species* thatSpecies_);

    // Evaluates the performance of the input `Organism`.
    virtual double evaluate(Organism* thatOrganism_);
};
