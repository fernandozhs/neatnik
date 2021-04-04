/*
  A `Chromosome` stores and manipulates a subset of an `Organism`'s `Genotype`.

  Data:
  ----
  logbook: an `std::unordered_map<unsigned long int, E*>` logging all `E` elements of a `Genotype`.
  genes: an `std::unordered_map<int, std::vector<E*>>` cataloguing the `E` elements of a `Genotype`.

  Constructor:
  -----------
  initialization: initializes this `Chromosome` in a clean slate.

  Destructor:
  ----------
  resursive: recursively deletes this `Chromosome` and all the `E` elements it encodes.

  Methods:
  -------
  size: retrieves the total number of encoded `E`s with matching role(s).
  begin: retrieves an iterator at the beginning of a given locus.
  end: retrieves an iterator at the end of a given locus.
  find: retrieves the `E*` with a matching key.
  insert: inserts an `E*` into this `Chromosome`.
  remove: removes an `E*` from this `Chromosome`.
  toggle: toggles the state of an encoded `E` element.
  random: selects a random `E*` with matching role(s) and state(s).
  retrieve: retrieves all `E*`s with matching role(s) and state(s).
  sort: sorts all `E*`s with matching role(s) and state(s) according to their identification tags.
  element_comparison: the criterion for comparing two `E*`s.
*/

/*
  Contributors: Fernando Zago and Hans Hopkins.
*/

#pragma once

#include <unordered_map>
#include <vector>
#include <utility>
#include <algorithm>
#include "../neatnik/neatnik.h"
#include "../utils/utils.h"

template <class E>
class Chromosome
{
public:

    // Data:

    // The log of all `E` elements in this `Chromosome`.
    std::unordered_map<unsigned long int, E*> logbook;

    // A catalog of `E` elements organized by their roles and states.
    std::unordered_map<int, std::vector<E*>> genes;


    // Constructors:

    // Constructor responsible for initializing this `Chromosome` in a clean slate.
    Chromosome();


    // Destructor:

    // Destructor responsible for recursively deleting this `Chromosome` and all the `E` elements it encodes.
    ~Chromosome();


    // Methods:

    // Retrieves the total number of encoded `E*`s with matching role(s).
    int size(const std::vector<int> roles_ = {1, 2, 3, 4}, const std::vector<int> states_ = {-1, 1});

    // Retrieves an iterator at the beginning of a given locus.
    typename std::vector<E*>::iterator begin(int locus_);

    // Retrieves an iterator at the end of a given locus.
    typename std::vector<E*>::iterator end(int locus_);

    // Retrieves the `E*` with a matching key.
    E* find(unsigned long int key_);

    // Inserts an `E*` into this `Chromosome`.
    E* insert(E* thatElement_);

    // Removes an `E*` from this `Chromosome`.
    E* remove(E* thatElement_);

    // Toggles the state of an encoded `E` element.
    void toggle(E* thatElement_, int state_);

    // Selects a random `E*` with matching role(s) and state(s).
    E* random(const std::vector<int> roles_ = {1, 2, 3, 4}, const std::vector<int> states_ = {-1, 1}, const std::vector<double> weights_ = {});

    // Retrieves all `E*`s with matching role(s) and state(s).
    std::vector<E*> retrieve(const std::vector<int> roles_ = {1, 2, 3, 4}, const std::vector<int> states_ = {-1, 1});

    // Sorts all `E*`s with matching role(s) and state(s) according to their identification tags.
    std::vector<E*> sort(const std::vector<int> roles_ = {1, 2, 3, 4}, const std::vector<int> states_ = {-1, 1});

    // The criterium for comparing two `E*`s.
    static bool element_comparison(E* thatElement_, E* thisElement_);
};
