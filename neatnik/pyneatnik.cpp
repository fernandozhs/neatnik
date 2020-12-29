#include "../neatnik/pyneatnik.h"

// Python Bindings:

// Binds all global variables and non-standard types to a Python module.
void bind_NEATnik(pybind11::module& m)
{
    // Non-standard Types:
    pybind11::enum_<element_type>(m, "ElementType")
        .value("NODE", NODE)
        .value("LINK", LINK)
        .export_values();

    pybind11::enum_<element_state>(m, "ElementState")
        .value("DISABLED", DISABLED)
        .value("ENABLED", ENABLED)
        .export_values();

    pybind11::enum_<link_role>(m, "LinkRole")
        .value("FORWARD", FORWARD)
        .value("RECURRENT", RECURRENT)
        .value("BIASING", BIASING)
        .value("LOOPED", LOOPED)
        .export_values();

    pybind11::enum_<node_role>(m, "NodeRole")
        .value("INPUT", INPUT)
        .value("HIDDEN", HIDDEN)
        .value("BIAS", BIAS)
        .value("OUTPUT", OUTPUT)
        .export_values();

    pybind11::enum_<node_activation>(m, "NodeActivation")
        .value("HEAVISIDE", HEAVISIDE)
        .value("RELU", RELU)
        .value("LOGISTIC", LOGISTIC)
        .value("IDENTITY", IDENTITY)
        .export_values();

    pybind11::enum_<taxon_group>(m, "TaxonGroup")
        .value("DOMINANT", DOMINANT)
        .value("CONTESTANT", CONTESTANT)
        .export_values();


    // General Parameters:
    m.attr("generational_cycles") = generational_cycles;
    m.attr("population_size") = population_size;
    m.attr("mutation_attempts") = mutation_attempts;
    m.attr("spawning_attempts") = spawning_attempts;
    m.attr("weight_bound") = weight_bound;
    m.attr("perturbation_power") = perturbation_power;
    m.attr("compatibility_weights") = compatibility_weights;
    m.attr("rejection_fraction") = rejection_fraction;
    m.attr("stagnation_threshold") = stagnation_threshold;
    m.attr("compatibility_threshold") = compatibility_threshold;


    // Probability Mass Functions:
    m.attr("enabling_link") = enabling_link;
    m.attr("altering_links") = altering_links;
    m.attr("altering_weight") = altering_weight;
    m.attr("adding_link") = adding_link;
    m.attr("enabling_node") = enabling_node;
    m.attr("altering_nodes") = altering_nodes;
    m.attr("altering_activation") = altering_activation;
    m.attr("adding_node") = adding_node;
    m.attr("assimilating_links") = assimilating_links;
    m.attr("assimilating_nodes") = assimilating_nodes;
    m.attr("assimilating_weight") = assimilating_weight;
    m.attr("assimilating_function") = assimilating_function;
    m.attr("spawning_organism") = spawning_organism;
}
