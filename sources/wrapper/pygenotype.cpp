#include "pygenotype.hpp"


void bind_Genotype(pybind11::module& m)
{
    pybind11::class_<Genotype>(m, "Genotype")

        // Properties:
        .def_readonly("nodes", &Genotype::nodes)
        .def_readonly("links", &Genotype::links)

        // Methods:
        .def("size", &Genotype::size);
}