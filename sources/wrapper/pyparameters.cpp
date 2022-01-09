#include "pyparameters.hpp"


void bind_Parameters(pybind11::module& m)
{
    pybind11::class_<Parameters>(m, "Parameters")

        // Properties:
        .def_readwrite_static("random_seed", &Parameters::random_seed)
        .def_readwrite_static("generational_cycles", &Parameters::generational_cycles)
        .def_readwrite_static("population_size", &Parameters::population_size)
        .def_readwrite_static("mutation_attempts", &Parameters::mutation_attempts)
        .def_readwrite_static("spawning_attempts", &Parameters::spawning_attempts)
        .def_readwrite_static("weight_bound", &Parameters::weight_bound)
        .def_readwrite_static("perturbation_power", &Parameters::perturbation_power)
        .def_readwrite_static("initial_activation", &Parameters::initial_activation)
        .def_readwrite_static("rejection_fraction", &Parameters::rejection_fraction)
        .def_readwrite_static("stagnation_threshold", &Parameters::stagnation_threshold)
        .def_readwrite_static("compatibility_threshold", &Parameters::compatibility_threshold)
        .def_readwrite_static("compatibility_weights", &Parameters::compatibility_weights)
        .def_readwrite_static("enabling_link", &Parameters::enabling_link)
        .def_readwrite_static("altering_links", &Parameters::altering_links)
        .def_readwrite_static("altering_weight", &Parameters::altering_weight)
        .def_readwrite_static("adding_link", &Parameters::adding_link)
        .def_readwrite_static("enabling_node", &Parameters::enabling_node)
        .def_readwrite_static("altering_nodes", &Parameters::altering_nodes)
        .def_readwrite_static("altering_activation", &Parameters::altering_activation)
        .def_readwrite_static("adding_node", &Parameters::adding_node)
        .def_readwrite_static("assimilating_links", &Parameters::assimilating_links)
        .def_readwrite_static("assimilating_nodes", &Parameters::assimilating_nodes)
        .def_readwrite_static("assimilating_weight", &Parameters::assimilating_weight)
        .def_readwrite_static("assimilating_activation", &Parameters::assimilating_activation)
        .def_readwrite_static("spawning_organism", &Parameters::spawning_organism)

        // Constructor:
        .def(pybind11::init<>());
}
