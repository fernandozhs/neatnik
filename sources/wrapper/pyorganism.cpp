#include "pyorganism.hpp"


void bind_Organism(pybind11::module& m)
{
    pybind11::class_<Organism>(m, "Organism")

        // Properties:
        .def_readwrite("species", &Organism::species)
        .def_readwrite("group", &Organism::group)
        .def_readwrite("age", &Organism::age)
        .def_readwrite("score", &Organism::score)

        // Constructor:
        .def(pybind11::init<Graph>())

        // Methods:
        .def("react", pybind11::overload_cast<>(&Organism::react))
        .def("react", pybind11::overload_cast<std::vector<std::vector<std::vector<double>>>>(&Organism::react))
        .def("graph", &Organism::graph)
        .def(pybind11::pickle(
            // __getstate__
            [](const Organism& organism_)
            {
                return organism_.graph();
            },
            // __setstate__
            [](Graph graph_)
            {
                return new Organism(graph_);
            }
        ));
}
