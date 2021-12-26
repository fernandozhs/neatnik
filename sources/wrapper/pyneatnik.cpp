#include "pyneatnik.hpp"


void bind_NEATnik(pybind11::module& m)
{
    // Non-standard Types:

    pybind11::enum_<driver_metric>(m, "DriverMetric")
        .value("NOVELTY", NOVELTY)
        .value("FITNESS", FITNESS)
        .export_values();

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
        .value("HIDDEN", HIDDEN)
        .value("OUTPUT", OUTPUT)
        .value("BIAS", BIAS)
        .value("INPUT", INPUT)
        .export_values();

    pybind11::enum_<node_activation>(m, "NodeActivation")
        .value("HEAVISIDE", HEAVISIDE)
        .value("RELU", RELU)
        .value("LOGISTIC", LOGISTIC)
        .value("IDENTITY", IDENTITY)
        .value("UNITY", UNITY)
        .export_values();

    pybind11::enum_<taxon_group>(m, "TaxonGroup")
        .value("DOMINANT", DOMINANT)
        .value("CONTESTANT", CONTESTANT)
        .export_values();
}
