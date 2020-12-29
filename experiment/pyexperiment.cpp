#include "../experiment/pyexperiment.h"

// Methods:

// Scores the performance of the input `Organism`.
double PyExperiment::performance(Organism* thatOrganism_)
{
    PYBIND11_OVERRIDE_PURE(double, Experiment, performance, thatOrganism_);
}


// Python Bindings:

// Binds the `Experiment` class to a Python module.
void bind_Experiment(pybind11::module& m)
{
    pybind11::class_<Experiment, PyExperiment>(m, "Experiment")

        // Data:
        .def_readwrite("genus", &Experiment::genus)

        // Constructor:
        .def(pybind11::init<Genus*>())

        // Methods:
        .def("evolve", &Experiment::evolve, pybind11::arg("cycles") = generational_cycles, pybind11::arg("verbose") = true)
        .def("evaluate", &Experiment::evaluate)
        .def("performance", &Experiment::performance);
}
