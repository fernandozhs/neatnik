/*
  Contributors: Fernando Zago and Hans Hopkins.
*/

#pragma once

#include <vector>
#include "../neatnik/neatnik.hpp"
#include "../organism/organism.hpp"

class Phenotype
{
public:

    // Properties:

    Organism* organism;

    std::vector<double> output;


    // Constructor:

    Phenotype(Organism* organism_);


    // Methods:

    void assemble();

    void disassemble();

    void activate(std::vector<double> inputs_);

    void deactivate();

    void discontinue();
};
