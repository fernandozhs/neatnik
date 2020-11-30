/*
  A `XOR` drives the evolution of an 'exclusive or' operator within a `Genus`.

  Methods:
  -------
  performance: scores the performance of the input `Phenotype`.
*/

/*
  Contributors: Fernando Zago.
*/

#pragma once

#include <tuple>
#include <vector>
#include <cmath>
#include "../experiment/experiment.h"

class XOR : public Experiment
{
public:

    // Methods:

    // Scores the performance of the input `Phenotype`.
    double performance(Phenotype* thatPhenotype_);
};
