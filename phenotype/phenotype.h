/*
  A `Phenotype` embodies the artificial neural network encoded by an `Organism`'s `Genotype`.

  Data:
  ----
  organism: the `Organism*` associated with this `Phenotype`.
  output: a `std::vector<double>` containing this `Phenotype`'s output.

  Constructor:
  ------------
  initialization: initializes this `Phenotype` and assigns it to its associated `Organism`.

  Methods:
  -------
  assemble: assembles this `Phenotype`.
  disassemble: disassembles this `Phenotype`.
  activate: propagates an input signal through this `Phenotype` and stores its output.
  deactivate: restores this `Phenotype` to a clean slate.
*/

/*
  Contributors: Fernando Zago and Hans Hopkins.
*/

#pragma once

#include <vector>
#include "../neatnik/neatnik.h"
#include "../organism/organism.h"

class Phenotype
{
public:

    // Data:

    // The `Organism*` associated with this `Phenotype`.
    Organism* organism;

    // This `Phenotype`'s output.
    std::vector<double> output;


    // Constructor:

    // Constructor responsible for initializing this `Phenotype` and assigns it to its associated `Organism`.
    Phenotype(Organism* organism_);


    // Methods:

    // Assembles this `Phenotype`.
    void assemble();

    // Disassembles this `Phenotype`.
    void disassemble();

    // Propagates an input signal through this `Phenotype` and stores its output.
    void activate(std::vector<double> inputs_);

    // Restores this `Phenotype` to a clean slate.
    void deactivate();
};
