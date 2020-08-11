/*
  An `Organism` encapsulates the `Genotype`, `Phenotype`, and score of an individual within a `Population`.

  Data:
  ----
  population: the `Population*` to which this `Organism` belongs.
  genotype: the `Genotype*` storing this `Organism`'s genetic information.
  phenotype: the `Phenotype*` embodying the artificial neural network encoded by this `Organism`'s `Genotype`.
  score: a `double` measuring this `Organism`'s performance with respect to a given metric.

  Constructor:
  -----------
  initialization: constructs an `Organism` characterized by a minimal, fully-connected `Phenotype`.
  copy: makes a deep copy of the input `Organism`.

  Destructor:
  ----------
  recursive: deletes this `Organism`, as well as its associated `Genotype` and `Phenotype`.

  Methods:
  -------
  mutate: mutates this `Organism`.
  crossover: assimilates another `Organism` through a crossover operation.

  Operator:
  --------
  <: compares the scores or `Genotype` lengths of two `Organism`s.
*/

#pragma once

#include "../neatnik/neatnik.h"
#include "../genotype/genotype.h"
#include "../phenotype/phenotype.h"

class Organism
{
public:

    // Data:

    // The `Population*` to which this `Organism` belongs.
    Population* population;

    // This `Organism`'s genetic make-up.
    Genotype* genotype;

    // The artificial neural network associated with this `Organism`.
    Phenotype* phenotype;

    // A measure of this `Organism`'s performance with respect to a given metric.
    double score = 0.;


    // Constructor:

    // Initialization constructor.
    // TODO: Make the `Genotype` initialization more flexible.
    Organism(Population* thatPopulation_, Archetype thatArchetype_);

    // Copy constructor responsible for making a deep copy of the input `Organism`.
    Organism(Organism* thatOrganism_);


    // Destructor:

    // Recursive destructor.
    ~Organism();


    // Methods:

    // Mutates this `Organism`.
    void mutate();

    // Assimilates another `Organism` through a crossover operation.
    void crossover(Organism* thatOrganism_);


    // Operator:

    // Overloaded '<' operation for comparing two `Organism`s' scores or `Genotype` lengths.
    bool operator <(const Organism& thatOrganism_) const;
};
