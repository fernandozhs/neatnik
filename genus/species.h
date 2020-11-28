/*
  A `Species` stores and manipulates the a collection of `Organism`s.

  Data:
  ----
  tag: a unique `unsigned integer` specifying this `Species`' identity within a `Genus`.
  batch: an `enum` (`object_batch`) specifying the batch to which this `Species` belongs.
  genus: the `Genus*` to which this `Species` belongs.
  organisms: a `Group<Organism>*` storing the `Organism`s which make up this `Species`.
  scores: a `double` storing this `Species`' score.

  Constructor:
  -----------
  initialization:  initializes this `Species` with `Organism`s characterized by minimal fully-connected `Genotype`s.
  spawning: spawns this `Species` from a single `Organism`.

  Destructor:
  ----------
  recursive: deletes this `Species` and its `Group<Organism>`.

  Methods:
  -------
  spawn: spawns a new `Organism` within this `Species`.
  spawn_organism: attempts to spawn a new `Organism` within this `Species`.
  elect_organisms: sifts out the rejected `Organism*`s from the matching batch(es).
  organism_compatibility: the compatibility criterion for `Organism*`s.
  organism_comparison: the criterion for comparing two `Organism*`s.
*/

/*
  Contributors: Fernando Zago.
*/

#pragma once

#include <vector>
#include <algorithm>
#include "../main/main.h"
#include "../genus/group.h"
#include "../genus/genus.h"
#include "../organism/organism.h"

class Species
{
public:

    // Data:

    // A unique label specifying this `Species`' identity within a `Genus`.
    unsigned int tag;

    // The batch to which this `Species` belongs.
    object_batch batch;

    // The `Genus` to which this `Species` belongs.
    Genus* genus;

    // A `Group<Organism>*`s storing the `Organism`s which make up this `Species`.
    Group<Organism>* organisms;

    // This `Species`' score.
    double score = -1.;


    // Constructor:

    // Initializes this `Species` with `Organism`s characterized by minimal fully-connected `Genotype`s.
    Species(unsigned int tag_, object_batch batch_, Genus* thatGenus_, std::vector<Archetype> thoseArchetypes_);

    // Spawns this `Species` from a single `Organism`.
    Species(unsigned int tag_, object_batch batch_, Genus* thatGenus_, Organism* thatOrganism_);


    // Destructor:

    // Recursive destructor.
    ~Species();


    // Methods:

    // Spawns a new `Organism` within this `Species`.
    Organism* spawn(Organism* thatOrganism_);

    // Spawns a new `Organism` within this `Species`.
    Organism* spawn(Organism* thatOrganism_, Organism* thisOrganism_);

    // Attempts to spawn a new `Organism` within this `Species`.
    Organism* spawn_organism(int attempts_ = spawning_attempts);

    // Sifts out the rejected `Organism*`s from the matching batch(es).
    void elect_organisms(const std::vector<int> batches_);

    // The compatibility criterion for `Organism*`s.
    bool organism_compatibility(Organism* thatOrganism_);

    // The criterion for comparing two `Organism*`s.
    static bool organism_comparison(Organism* thatOrganism_, Organism* thisOrganism_);
};
