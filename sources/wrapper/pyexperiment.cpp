#include "pyexperiment.hpp"


void PyExperiment::display()
{
    PYBIND11_OVERRIDE(void, Experiment, display);
}

double PyExperiment::fitness(Organism* thatOrganism_)
{
    PYBIND11_OVERRIDE_PURE(double, Experiment, fitness, thatOrganism_);
}

void bind_Experiment(pybind11::module& m)
{
    pybind11::class_<Experiment, PyExperiment>(m, "Experiment")

        // Properties:
        .def_readwrite("MPI_rank", &Experiment::MPI_rank)
        .def_readwrite("MPI_size", &Experiment::MPI_size)
        .def_readwrite("vertexes", &Experiment::vertexes)
        .def_readwrite("edges", &Experiment::edges)
        .def_readwrite("stimuli", &Experiment::stimuli)
        .def_readwrite("genus", &Experiment::genus)

        // Constructor:
        .def(pybind11::init<>())

        // Methods:
        .def("run", &Experiment::run)
        .def("score", &Experiment::score)
        .def("display", &Experiment::display)
        .def("fitness", &Experiment::fitness);
}
