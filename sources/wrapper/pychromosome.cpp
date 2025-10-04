#include "pychromosome.hpp"


void bind_Chromosome(pybind11::module& m)
{
    pybind11::class_<Chromosome<Node>>(m, "NodeChromosome")

        // Methods:
        .def("size", &Chromosome<Node>::size);


    pybind11::class_<Chromosome<Link>>(m, "LinkChromosome")

        // Methods:
        .def("size", &Chromosome<Link>::size);
}