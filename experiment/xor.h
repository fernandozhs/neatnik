/*
  A `XOR` drives the evolution of an 'exclusive or' operator within a `Genus`.

  Methods:
  -------
  evaluate: evaluates the performance of the input `Organism`.
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

    // Evaluates the performance of the input `Organism`.
    double evaluate(Organism* thatOrganism_);
};
