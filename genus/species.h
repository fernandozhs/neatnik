/*
  A `Species` stores and manages a collection of `Organism`s.

  Data:
  ----
  genus: a `Genus*` specifying the taxon to which this `Species` belongs.
  group: an `enum` (`taxon_group`) specifying the group to which this `Species` belongs within its taxon.
  organisms: an `std::unordered_map<int, std::vector<Organism*>>` cataloguing all `Organism`s in this `Species`.
  rank: a `double` storing this `Species`' rank.

  Constructor:
  -----------
  initialization: initializes this `Species` with `Organism`s characterized by minimal fully-connected `Genotype`s.
  speciation: originates this `Species` from its first `Organism`.

  Destructor:
  ----------
  recursive: deletes this `Species` and all its `Organism`s.

  Methods:
  -------
  size: retrieves the total number of stored `Organism`s from the matching group(s).
  begin: retrieves an iterator at the beginning of a given group.
  end: retrieves an iterator at the end of a given group.
  front: retrieves the first `Organism*` of a given group.
  back: retrieves the last `Organism*` of a given group.
  insert: inserts an `Organism*`s into this `Species`.
  remove: removes an `Organism*`s from this `Species`.
  purge: purges `Organism*`s from this `Species`.
  toggle: toggles the group associated with the input `Organism*`.
  random: selects a random `Organism*` from the matching group(s).
  retrieve: retrieves all `Organism*`s from the matching group(s).
  sort: sorts all `Organism*`s from the matching group(s) according to their performance.
  select: finds the best performing `Organism` and purges a fraction of the remainder.
  spawn: attempts to issue a new `Organism`.
  organism_compatibility: the compatibility criterion for `Organism*`s.
  organism_comparison: the criterion for comparing two `Organism*`s.
*/

/*
  Contributors: Fernando Zago.
*/

#pragma once

#include <unordered_map>
#include <vector>
#include <algorithm>
#include "../main/main.h"
#include "../utils/utils.h"
#include "../genus/genus.h"
#include "../organism/organism.h"

class Species
{
public:

    // Data:

    // The taxon to which this `Species` belongs.
    Genus* genus;

    // The group to which this `Species` belongs.
    taxon_group group;

    // A catalog of `Organism*`s organized by group.
    std::unordered_map<int, std::vector<Organism*>> organisms;

    // This `Species`' rank.
    double rank = -1.;


    // Constructor:

    // Initializes this `Species` with `Organism`s characterized by minimal fully-connected `Genotype`s.
    Species(Genus* thatGenus_, taxon_group group_, std::vector<Archetype> thoseArchetypes_);

    // Originates this `Species` from its first `Organism`.
    Species(Genus* thatGenus_, taxon_group group_, Organism* thatOrganism_);


    // Destructor:

    // Recursive destructor responsible for deleting this `Species` and all its `Organism`s.
    ~Species();


    // Methods:

    // Retrieves the total number of stored `Organism`s from the matching group(s).
    int size(const std::vector<int> groups_ = {0, 1});

    // Retrieves an iterator at the beginning of a given group.
    typename std::vector<Organism*>::iterator begin(int group_);

    // Retrieves an iterator at the end of a given group.
    typename std::vector<Organism*>::iterator end(int group_);

    // Retrieves the first `Organism*` of a given group.
    Organism* front(int group_);

    // Retrieves the last `Organism*` of a given group.
    Organism* back(int group_);

    // Inserts an `Organism*`s into this `Species`.
    Organism* insert(Organism* thatObject_);

    // Removes an `Organism*`s from this `Species`.
    Organism* remove(Organism* thatObject_);

    // Purges an `Organism*` from this `Species`.
    void purge(Organism* thatOrganism_);

    // Purges all `Organism*`s from the matching group(s).
    void purge(const std::vector<int> groups_ = {0, 1});

    // Toggles the group associated with the input `Organism*`.
    void toggle(Organism* thatObject_, int group_);

    // Selects a random `Organism*` from the matching group(s).
    Organism* random(const std::vector<int> groups_ = {0, 1}, const std::vector<double> weights_ = {});

    // Retrieves all `Organism*`s from the matching group(s).
    std::vector<Organism*> retrieve(const std::vector<int> groups_ = {0, 1});

    // Sorts all `Organism*`s from the matching group(s) according to their performance.
    std::vector<Organism*> sort(const std::vector<int> groups_ = {0, 1});

    // Finds the best performing `Organism` and purges a fraction of the remainder.
    void select();

    // Attempts to issue a new `Organism`.
    Organism* spawn(int attempts_ = spawning_attempts);

    // The compatibility criterion for `Organism*`s.
    bool organism_compatibility(Organism* thatOrganism_);

    // The criterion for comparing two `Organism*`s.
    static bool organism_comparison(Organism* thatOrganism_, Organism* thisOrganism_);
};
