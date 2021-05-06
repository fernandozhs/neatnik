/*
  Python bindings for the `Experiment` class.
*/

/*
  Contributors: Fernando Zago.
*/

#include "../experiment/experiment.h"
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>


// Defines a `PyExperiment`.
class PyExperiment : public Experiment
{
public:

    // Inherited constructor:
    using Experiment::Experiment;


    // Methods:

    // Displays any of this `Experiment`'s current data.
    void display() override;

    // Evaluates the input `Organism`'s FITNESS score.
    double fitness(Organism* thatOrganism_) override;

    // Extracts the input `Organism`'s behavior.
    std::vector<double> behavior(Organism* thatOrganism_) override;
};

// Binds the `Experiment` class to a Python module.
void bind_Experiment(pybind11::module& m);
