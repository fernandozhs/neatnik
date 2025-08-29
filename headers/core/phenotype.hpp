/*
  Contributors: Fernando Zago and Hans Hopkins.
*/

#pragma once

#include <vector>
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include "neatnik.hpp"
#include "organism.hpp"


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

    void activate(const double* inputs_begin_, double* outputs_begin_);

    void deactivate();

    void discontinue();
};
