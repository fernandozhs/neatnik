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
        .def_readonly("MPI_rank", &Experiment::MPI_rank)
        .def_readonly("MPI_size", &Experiment::MPI_size)
        .def_readonly("genus", &Experiment::genus)

        // Constructor:
        .def(pybind11::init<>())

        // Methods:
        .def("display", &Experiment::display)
        .def("fitness", &Experiment::fitness)
        .def("set", pybind11::overload_cast<std::vector<std::vector<std::vector<double>>>>(&Experiment::set), pybind11::arg("stimuli"))
        .def("set", pybind11::overload_cast<GenotypeData>(&Experiment::set), pybind11::arg("population"))
        .def("set", pybind11::overload_cast<GenusData>(&Experiment::set), pybind11::arg("population"))
        .def("run", [](Experiment& self)
        {
            if (self.genus->size() == 0)
            {
                throw std::runtime_error("Cannot run experiment: population has not been seeded.");
            }
            if (self.stimuli.empty())
            {
                throw std::runtime_error("Cannot run experiment: no stimuli have been provided.");
            }
            self.run();
        });
}
