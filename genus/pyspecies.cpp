#include "../genus/pyspecies.h"

// Python Bindings:

// Binds the `Species` class to a Python module.
void bind_Species(pybind11::module& m)
{
    pybind11::class_<Species>(m, "Species")

        // Data:
        .def_readwrite("genus", &Species::genus)
        .def_readwrite("group", &Species::group)
        .def_readwrite("rank", &Species::rank)

        // Methods:
        .def("size", &Species::size);
}
