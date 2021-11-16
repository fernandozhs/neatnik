#include "../genus/pygenus.hpp"

// Python Bindings:

// Binds the `Genus` class to a Python module.
void bind_Genus(pybind11::module& m)
{
    pybind11::class_<Genus>(m, "Genus")

        // Methods:
        .def("size", &Genus::size);
}
