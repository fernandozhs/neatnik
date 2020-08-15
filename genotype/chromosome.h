/*
  A `Chromosome` stores and manipulates a subset of an `Organism`'s `Genotype`.

  Data:
  ----
  genes: an unordered map between `integer`s and `std::vector<E*>`s encoding the `E` (`Node` or `Link`) elements of a `Genotype`.

  Constructors:
  ------------
  initialization: creates an empty `Chromosome`.
  copy: makes a deep copy of the input `Chromosome`.

  Destructor:
  ----------
  resursive: recursively deletes this `Chromosome`'s entire genetic make-up.

  Methods:
  -------
  size: retrieves the total number of stored `E*`s with matching role(s).
  begin: returns an iterator at the beginning of a given locus.
  end: returns an iterator at the end of a given locus.
  insert: inserts a `E*` into this `Chromosome`.
  remove: removes a `E*` from this `Chromosome`.
  toggle: toggles the state of an encoded `E` element.
  match: finds the `E*` with a matching identification tag.
  random: selects a random `E*` with matching role(s) and state(s).
  retrieve: retrieves all `E*`s with matching role(s) and state(s).
  sort: sorts all `E*`s with matching role(s) and state(s) according to their identification tag.
  crossover: assimilates another `Chromosome` through a crossover operation.
  compatibility: assesses the compatibility with another `Chromosome`.
*/

/*
  Contributors: Fernando Zago and Hans Hopkins.
*/

#pragma once

#include <unordered_map>
#include <vector>
#include <algorithm>
#include "../neatnik/neatnik.h"
#include "../utils/utils.h"

template <class E>
class Chromosome
{
public:

    // Data:

    // An unordered map between `integer`s and `std::vector<E*>`s encoding `E` (`Node` or `Link`) elements
    std::unordered_map<int, std::vector<E*>> genes;


    // Constructors:

    // Initialization constructor responsible for creating an empty `Chromosome`.
    Chromosome();

    // Copy constructor responsible for making a deep copy of the input `Chromosome`.
    Chromosome(Chromosome<E>* thatChromosome_);


    // Destructor:

    // Recursive destructor.
    ~Chromosome();


    // Methods:

    // Retrieves the total number of stored `E*`s with matching role(s).
    int size(const std::vector<int> roles_ = {1, 2, 3, 4}, const std::vector<int> states_ = {-1, 1});

    // Returns an iterator at the beginning of a given locus.
    typename std::vector<E*>::iterator begin(int locus_);

    // Returns an iterator at the end of a given locus.
    typename std::vector<E*>::iterator end(int locus_);

    // Inserts a `E*` into this `Chromosome`.
    void insert(E* element_);

    // Removes a `E*` from this `Chromosome`.
    void remove(E* element_);

    // Toggles the state of an encoded `E` element.
    void toggle(E* element_);

    // Finds the `E*` with a matching identification tag.
    E* match(E* element_);

    // Selects a random `E*` with matching role(s) and state(s).
    E* random(const std::vector<int> roles_ = {1, 2, 3, 4}, const std::vector<int> states_ = {-1, 1});

    // Retrieves all `E*`s with matching role(s) and state(s).
    std::vector<E*> retrieve(const std::vector<int> roles_ = {1, 2, 3, 4}, const std::vector<int> states_ = {-1, 1});

    // Sorts all `E*`s with matching role(s) and state(s) according to their identification tag.
    std::vector<E*> sort(const std::vector<int> roles_ = {1, 2, 3, 4}, const std::vector<int> states_ = {-1, 1});

    // Assimilates another `Chromosome` through a crossover operation.
    void crossover(Chromosome<E>* thatChromosome_);

    // Assesses the compatibility with another `Chromosome`.
    // TODO: Make this method more flexible by implementing tunable parameters, as well as more fine-grained by distinguishing matching elements by their internal parameters.
    double compatibility(Chromosome<E>* thatChromosome_);
};
