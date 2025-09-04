#include "pyexperiment.hpp"


void PyExperiment::display()
{
    PYBIND11_OVERRIDE(void, Experiment, display);
}

void PyExperiment::execute()
{
    PYBIND11_OVERRIDE(void, Experiment, execute);
}

double PyExperiment::fitness(Organism* thatOrganism_)
{
    PYBIND11_OVERRIDE_PURE(double, Experiment, fitness, thatOrganism_);
}

void bind_Experiment(pybind11::module& m)
{
    pybind11::class_<Experiment, PyExperiment>(m, "Experiment")

        // Properties:
        .def_readonly("MPI_rank", &Experiment::MPI_rank)
        .def_readonly("MPI_size", &Experiment::MPI_size)
        .def_readonly("stimuli", &Experiment::stimuli)
        .def_readonly("genus", &Experiment::genus)

        // Constructor:
        .def(pybind11::init<>())

        // Methods:
        .def("display", &Experiment::display)
        .def("execute", &Experiment::execute)
        .def("fitness", &Experiment::fitness)
        .def("initialize", &Experiment::initialize)
        .def("finalize", &Experiment::finalize)
        .def("set", pybind11::overload_cast<pybind11::array_t<double>>(&Experiment::set), pybind11::arg("stimuli"))
        .def("set", pybind11::overload_cast<GenotypeData>(&Experiment::set), pybind11::arg("population"))
        .def("set", pybind11::overload_cast<GenusData>(&Experiment::set), pybind11::arg("population"))
        .def("run", &Experiment::run);
}
