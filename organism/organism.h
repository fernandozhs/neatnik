/*
  An `Organism` encapsulates the `Genotype` and `Phenotype`, and score of an individual within a `Species`.

  Data:
  ----
  species: the `Species*` to which this `Organism` belongs.
  genotype: the `Genotype*` storing this `Organism`'s genetic information.
  phenotype: the `Phenotype*` embodying the artificial neural network encoded by this `Organism`'s `Genotype`.
  batch: an `enum` (`object_batch`) labeling the batch to which this `Organism` belongs within a `Species`.
  age: an `integer` storing this `Organism`'s age.
  score: a `double` storing this `Organism`'s score.

  Constructor:
  -----------
  initialization: constructs an `Organism` characterized by a minimal, fully-connected `Phenotype`.
  copy: makes a deep copy of the input `Organism`.

  Destructor:
  ----------
  recursive: deletes this `Organism`, as well as its associated `Genotype` and `Phenotype`.

  Methods:
  -------
  mutate: produces a new `Organism` through mutation.
  assimilate: produces a new `Organism` through assimilation.
*/

#pragma once

#include "../main/main.h"
#include "../genotype/genotype.h"
#include "../phenotype/phenotype.h"
#include "../genus/species.h"

class Organism
{
public:

    // Data:

    // The `Species*` to which this `Organism` belongs.
    Species* species;

    // This `Organism`'s genetic make-up.
    Genotype* genotype;

    // The artificial neural network associated with this `Organism`.
    Phenotype* phenotype;

    // Establishes the batch to which this `Organism` belongs.
    object_batch batch;

    // This `Organism`'s age.
    int age;

    // This `Organism`'s score.
    double score;


    // Constructor:

    // Initialization constructor.
    // TODO: Make the `Genotype` initialization more flexible.
    Organism(Species* thatSpecies_, Archetype thatArchetype_);

    // Copy constructor responsible for making a deep copy of the input `Organism`.
    Organism(Organism* thatOrganism_);


    // Destructor:

    // Recursive destructor.
    ~Organism();


    // Methods:

    // Produces a new `Organism` through mutation.
    Organism* mutate();

    // Produces a new `Organism` through assimilation.
    Organism* assimilate(Organism* thatOrganism_);
};
