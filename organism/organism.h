/*
  An `Organism` encapsulates the `Genotype`, `Phenotype`, age, and score of an individual within a `Species`.

  Data:
  ----
  species: a `Species*` specifying the taxon to which this `Organism` belongs.
  group: an `enum` (`taxon_group`) specifying the group to which this `Organism` belongs within its taxon.
  genotype: the `Genotype*` storing this `Organism`'s genetic information.
  phenotype: the `Phenotype*` embodying the artificial neural network encoded by this `Organism`'s `Genotype`.
  age: an `integer` storing this `Organism`'s age.
  score: a `double` storing this `Organism`'s score.

  Constructors:
  ------------
  initialization: builds an `Organism` characterized by a minimal `Graph`.
  copy: makes a deep copy of the input `Organism`.
  reconstruction: constructs an `Organism` from an input `Graph`.

  Destructor:
  ----------
  recursive: deletes this `Organism`, as well as its associated `Genotype` and `Phenotype`.

  Methods:
  -------
  mutate: produces a new `Organism` through mutation.
  assimilate: produces a new `Organism` through assimilation.
  react: prompts this `Organism` to react to the input stimuli.
  graph: produces the `Graph` associated with this `Organism`'s `Genotype`.
*/

#pragma once

#include "../neatnik/neatnik.h"
#include "../genotype/genotype.h"
#include "../phenotype/phenotype.h"
#include "../genus/species.h"

class Organism
{
public:

    // Data:

    // The taxon to which this `Organism` belongs.
    Species* species;

    // The group to which this `Organism` belongs.
    taxon_group group;

    // This `Organism`'s genetic make-up.
    Genotype* genotype;

    // The artificial neural network associated with this `Organism`.
    Phenotype* phenotype;

    // This `Organism`'s age.
    int age;

    // This `Organism`'s score.
    double score;


    // Constructors:

    // Initialization constructor responsible for building an `Organism` characterized by a minimal `Graph`.
    Organism(Species* thatSpecies_, Graph thatGraph_);

    // Copy constructor responsible for making a deep copy of the input `Organism`.
    Organism(Organism* thatOrganism_);

    // Constructs an `Organism` from an input `Graph`.
    Organism(Graph thatGraph_);


    // Destructor:

    // Recursive destructor.
    ~Organism();


    // Methods:

    // Produces a new `Organism` through mutation.
    Organism* mutate();

    // Produces a new `Organism` through assimilation.
    Organism* assimilate(Organism* thatOrganism_);

    // Prompts this `Organism` to react to the input stimuli.
    std::vector<std::vector<double>> react(std::vector<std::vector<double>> stimuli_);

    // Produces the `Graph` associated with this `Organism`'s `Genotype`.
    Graph graph();
};
