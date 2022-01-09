/*
  Contributors: Fernando Zago.
*/

#include "experiment.hpp"
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>


class PyExperiment : public Experiment
{
public:

    // Inherited Constructor:

    using Experiment::Experiment;


    // Methods:

    void display() override;

    double fitness(Organism* thatOrganism_) override;
};


void bind_Experiment(pybind11::module& m);
