/*
  A `Group` stores and manages a collection of objects `O`.

  Data:
  ----
  objects: an `std::unordered_map<int, std::vector<O*>>` cataloguing all `O` objects stored in this `Group`.

  Constructor:
  -----------
  initialization: creates an empty `Group`.

  Destructor:
  ----------
  recursive: deletes this `Group` and all its `O` objects.

  Methods:
  -------
  size: retrieves the total number of stored `O`s from the matching batch(es).
  begin: retrieves an iterator at the beginning of a given batch.
  end: retrieves an iterator at the end of a given batch.
  front: retrieves the first `O*` of a given batch.
  back: retrieves the last `O*` of a given batch.
  insert: inserts an `O*`s into this `Group`.
  remove: removes an `O*`s from this `Group`.
  toggle: toggles the batch associated with the input `O*`.
  random: selects a random `O*` from the matching batch(es).
  retrieve: retrieves all `O*`s from the matching batch(es).
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

template <class O>
class Group
{
private:

    // Data:

    // A catalog of `O*` objects organized by batch.
    std::unordered_map<int, std::vector<O*>> objects;


public:

    // Constructor:

    // Initialization constructor responsible for creating an empty `Group`.
    Group();


    // Destructor:

    // Recursive destructor responsible for deleting this `Group` and all its `O`s.
    ~Group();


    // Methods:

    // Retrieves the total number of stored `O`s from the matching batch(es).
    int size(const std::vector<int> batches_ = {0, 1, 2, 3});

    // Retrieves an iterator at the beginning of a given batch.
    typename std::vector<O*>::iterator begin(int batch_);

    // Retrieves an iterator at the end of a given batch.
    typename std::vector<O*>::iterator end(int batch_);

    // Retrieves the first `O*` of a given batch.
    O* front(int batch_);

    // Retrieves the last `O*` of a given batch.
    O* back(int batch_);

    // Inserts an `O*`s into this `Group`.
    O* insert(O* thatObject_);

    // Removes an `O*`s from this `Group`.
    O* remove(O* thatObject_);

    // Toggles the batch associated with the input `O*`.
    void toggle(O* thatObject_, int batch_);

    // Selects a random `O*` from the matching batch(es).
    O* random(const std::vector<int> batches_ = {0, 1, 2, 3}, const std::vector<double> weights_ = {});

    // Retrieves all `O*`s from the matching batch(es).
    std::vector<O*> retrieve(const std::vector<int> batches_ = {0, 1, 2, 3});
};
