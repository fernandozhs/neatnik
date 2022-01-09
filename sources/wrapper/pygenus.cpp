#include "pygenus.hpp"


void bind_Genus(pybind11::module& m)
{
    pybind11::class_<Genus>(m, "Genus")

        // Properties:
        .def_readwrite("species", &Genus::species)
        .def_readwrite("scores", &Genus::scores)

        // Methods:
        .def("size", &Genus::size)
        .def("random", &Genus::random)
        .def("retrieve", &Genus::retrieve)
        .def("sort", &Genus::sort);
}
