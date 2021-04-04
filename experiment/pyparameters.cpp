#include "../experiment/pyparameters.h"

// Python Bindings:

// Binds the `Parameters` class to a Python module.
void bind_Parameters(pybind11::module& m)
{
    pybind11::class_<Parameters>(m, "Parameters")

        // Data:
        .def_readwrite("generational_cycles", &Parameters::generational_cycles)
        .def_readwrite("population_size", &Parameters::population_size)
        .def_readwrite("mutation_attempts", &Parameters::mutation_attempts)
        .def_readwrite("spawning_attempts", &Parameters::spawning_attempts)
        .def_readwrite("weight_bound", &Parameters::weight_bound)
        .def_readwrite("perturbation_power", &Parameters::perturbation_power)
        .def_readwrite("initial_activation", &Parameters::initial_activation)
        .def_readwrite("rejection_fraction", &Parameters::rejection_fraction)
        .def_readwrite("stagnation_threshold", &Parameters::stagnation_threshold)
        .def_readwrite("compatibility_threshold", &Parameters::compatibility_threshold)
        .def_readwrite("compatibility_weights", &Parameters::compatibility_weights)
        .def_readwrite("enabling_link", &Parameters::enabling_link)
        .def_readwrite("altering_links", &Parameters::altering_links)
        .def_readwrite("altering_weight", &Parameters::altering_weight)
        .def_readwrite("adding_link", &Parameters::adding_link)
        .def_readwrite("enabling_node", &Parameters::enabling_node)
        .def_readwrite("altering_nodes", &Parameters::altering_nodes)
        .def_readwrite("altering_activation", &Parameters::altering_activation)
        .def_readwrite("adding_node", &Parameters::adding_node)
        .def_readwrite("assimilating_links", &Parameters::assimilating_links)
        .def_readwrite("assimilating_nodes", &Parameters::assimilating_nodes)
        .def_readwrite("assimilating_weight", &Parameters::assimilating_weight)
        .def_readwrite("assimilating_activation", &Parameters::assimilating_activation)
        .def_readwrite("spawning_organism", &Parameters::spawning_organism)

        // Constructor:
        .def(pybind11::init<>());
}
