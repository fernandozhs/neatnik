#include "pygenotype.hpp"


void bind_Genotype(pybind11::module& m)
{
    pybind11::class_<Genotype>(m, "Genotype")

        // Methods:
        .def("size", &Genotype::size);
}