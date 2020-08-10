/*
  A `Species` ...

  Data:
  ----
  organisms: a `std::vector<Organism*>` listing all individuals belonging to this `Species`.
  ...

  Constructors:
  ------------
  ...

  Methods:
  -------
  ...
*/

#pragma once

#include <vector>
#include "../neatnik/neatnik.h"
#include "../organism/organism.h"

class Species
{
private:

    // Data:

    // The collection of `Organism*`s belonging to this `Species`.
    std::vector<Organism*> organisms;


public:

    // Constructor:

    // Initialization constructor.
    Species();


    // Methods:

};
