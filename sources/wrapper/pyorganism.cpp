#include "pyorganism.hpp"


void bind_Organism(pybind11::module& m)
{
    pybind11::class_<Organism>(m, "Organism")

        // Properties:
        .def_readonly("species", &Organism::species)
        .def_readonly("group", &Organism::group)
        .def_readonly("age", &Organism::age)
        .def_readonly("score", &Organism::score)

        // Constructor:
        .def(pybind11::init<OrganismData>())

        // Methods:
        .def("react", pybind11::overload_cast<>(&Organism::react))
        .def("react", pybind11::overload_cast<pybind11::array_t<double>>(&Organism::react), pybind11::arg("stimuli"))
        .def("data", &Organism::data)
        .def(pybind11::pickle(
            // __getstate__
            [](const Organism& organism_)
            {
                return organism_.data();
            },
            // __setstate__
            [](OrganismData data_)
            {
                return new Organism(data_);
            }
        ));
}
