#include "../organism/pyorganism.h"

// Python Bindings:

// Binds the `Organism` class to a Python module.
void bind_Organism(pybind11::module& m)
{
    pybind11::class_<Organism>(m, "Organism")

        // Data:
        .def_readwrite("species", &Organism::species)
        .def_readwrite("group", &Organism::group)
        .def_readwrite("age", &Organism::age)
        .def_readwrite("score", &Organism::score)

        // Constructors:
        .def(pybind11::init<Graph>())

        // Methods:
        .def("react", &Organism::react)
        .def("graph", &Organism::graph);
}
