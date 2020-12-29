#include "../genus/pygenus.h"

// Python Bindings:

// Binds the `Genus` class to a Python module.
void bind_Genus(pybind11::module& m)
{
    pybind11::class_<Genus>(m, "Genus")

        // Constructor:
        .def(pybind11::init<std::vector<Graph>>())

        // Methods:
        .def("size", &Genus::size);
}
