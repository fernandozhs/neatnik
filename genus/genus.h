/*
  A `Genus` stores and manipulates the a collection of `Species`.

  Data:
  ----
  neatnik: the `Neatnik*` responsible for controling this `Genus`' evolution.
  species: a `Group<Species>*` storing the `Species` which make up this `Genus`.

  Constructor:
  -----------
  initialization: initializes this `Genus` with a batch containing a single `Species`.

  Destructor:
  ----------
  recursive: deletes this `Genus` and its `Group<Species>`.

  Methods:
  -------
  spawn: spawns a new `Species` within this `Genus`.
  spawn_organisms: spawns a new generation of `Organism`s within this `Genus`.
  allocate_organisms: allocates a new generation of `Organism` to new or existing `Species`.
  elect_species: sifts out the rejected `Species*`s from the matching batch(es).
  species_rejection: the criterion for rejecting a `Species*`.
  species_comparison: the criterion for comparing two `Species*`s.
*/

/*
  Contributors: Fernando Zago.
*/

#pragma once

#include <vector>
#include <algorithm>
#include "../main/main.h"
#include "../genus/group.cpp"
#include "../neatnik/neatnik.h"
#include "../genus/species.h"

class Genus
{
public:

    // Data:

    // The `Neatnik` responsible for controling this `Genus`' evolution.
    Neatnik* neatnik;

    // A `Group<Species>*`s storing the `Species` which make up this `Genus`.
    static inline Group<Species>* species = new Group<Species>();


    // Constructor:

    // Initializes this `Genus` with a batch containing a single `Species`.
    Genus(Neatnik* thatNeatnik_, std::vector<Archetype> thoseArchetypes_);


    // Destructor:

    // Recursive destructor.
    ~Genus();


    // Methods:

    // Spawns a new `Species` within this `Genus`.
    Species* spawn(Organism* thatOrganism_);

    // Spawns a new generation of `Organism`s within this `Genus`.
    std::vector<Organism*> spawn_organisms();

    // Allocates a new generation of `Organism` to new or existing `Species`.
    void allocate_organisms();

    // Sifts out the rejected `Species*`s from the matching batch(es).
    void elect_species(const std::vector<int> batches_);

    // The criterion for rejecting a `Species*`.
    static bool species_rejection(Species* thatSpecies_);

    // The criterion for comparing two `Species*`s.
    static bool species_comparison(Species* thatSpecies_, Species* thisSpecies_);
};
