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

    // Scores the performance of the input `Organism`.
    double performance(Organism* thatOrganism_) override;
};

// Binds the `Experiment` class to a Python module.
void bind_Experiment(pybind11::module& m);
