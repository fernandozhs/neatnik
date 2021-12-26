#include "pyexperiment.hpp"

// Methods:

// Displays any of this `Experiment`'s current data.
void PyExperiment::display()
{
    PYBIND11_OVERRIDE(void, Experiment, display);
}

// Evaluates the input `Organism`'s FITNESS score.
double PyExperiment::fitness(Organism* thatOrganism_)
{
    PYBIND11_OVERRIDE_PURE(double, Experiment, fitness, thatOrganism_);
}

// Evaluates the input `Organism`'s FITNESS score.
std::vector<double> PyExperiment::behavior(Organism* thatOrganism_)
{
    PYBIND11_OVERRIDE_PURE(std::vector<double>, Experiment, behavior, thatOrganism_);
}


// Python Bindings:

// Binds the `Experiment` class to a Python module.
void bind_Experiment(pybind11::module& m)
{
    pybind11::class_<Experiment, PyExperiment>(m, "Experiment")

        // Data:
        //.def_readwrite("parameters", &Experiment::parameters)
        .def_readwrite("vertexes", &Experiment::vertexes)
        .def_readwrite("edges", &Experiment::edges)
        .def_readwrite_static("stimuli", &Experiment::stimuli)
        .def_readwrite("genus", &Experiment::genus)
        .def_readwrite("behaviors", &Experiment::behaviors)
        .def_readwrite("outcome", &Experiment::outcome)

        // Constructor:
        .def(pybind11::init<>())

        // Methods:
        .def("build", &Experiment::build)
        .def("run", &Experiment::run)
        .def("display", &Experiment::display)
        .def("fitness", &Experiment::fitness)
        .def("behavior", &Experiment::behavior);
}
