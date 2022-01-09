/*
  Contributors: Fernando Zago.
*/

#pragma once

#include <vector>
#include "neatnik.hpp"


class Parameters
{
public:

    // Properties:

    static unsigned int random_seed;

    static int generational_cycles;

    static int population_size;

    static int mutation_attempts;

    static int spawning_attempts;

    static double weight_bound;

    static double perturbation_power;

    static double splitting_priority;

    static node_activation initial_activation;

    static double rejection_fraction;

    static int stagnation_threshold;

    static double compatibility_threshold;

    static std::vector<double> compatibility_weights;

    static std::vector<double> enabling_link;

    static std::vector<double> altering_links;

    static std::vector<double> altering_weight;

    static std::vector<double> adding_link;

    static std::vector<double> enabling_node;

    static std::vector<double> altering_nodes;

    static std::vector<double> altering_activation;

    static std::vector<double> adding_node;

    static std::vector<double> assimilating_links;

    static std::vector<double> assimilating_nodes;

    static std::vector<double> assimilating_weight;

    static std::vector<double> assimilating_activation;

    static std::vector<double> spawning_organism;


    // Constructor:

    Parameters();


    // Destructor:

    ~Parameters();
};
