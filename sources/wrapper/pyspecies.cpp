#include "pyspecies.hpp"


void bind_Species(pybind11::module& m)
{
    pybind11::class_<Species>(m, "Species")

        // Properties:
        .def_readonly("group", &Species::group)
        .def_readonly("organisms", &Species::organisms)
        .def_readonly("rank", &Species::rank)

        // Methods:
        .def("size", &Species::size)
        .def("random", &Species::random)
        .def("retrieve", &Species::retrieve)
        .def("sort", &Species::sort);
}
