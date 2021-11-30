#include "../organism/pyorganism.hpp"

// Python Bindings:

// Binds the `Organism` class to a Python module.
void bind_Organism(pybind11::module& m)
{
    pybind11::class_<Organism>(m, "Organism")

        // Data:
        .def_readwrite("species", &Organism::species)
        .def_readwrite("group", &Organism::group)
        .def_readwrite("age", &Organism::age)
        .def_readwrite("scores", &Organism::scores)
        .def_readwrite("behavior", &Organism::behavior)

        // Constructor:
        .def(pybind11::init<Graph>())

        // Methods:
        .def("react", pybind11::overload_cast<>(&Organism::react))
        .def("react", pybind11::overload_cast<std::vector<std::vector<std::vector<double>>>>(&Organism::react))
        .def("graph", &Organism::graph)
        .def(pybind11::pickle(
            // __getstate__
            [](const Organism& thatOrganism_)
            {
                return thatOrganism_.graph();
            },
            // __setstate__
            [](Graph thatGraph_)
            {
                return new Organism(thatGraph_);
            }
        ));
}
