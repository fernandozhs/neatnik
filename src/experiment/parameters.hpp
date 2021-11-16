/*
  The `Parameters` class encapsulates all the parameters which characterize an `Experiment`.

  Data:
  ----
  evolution_driver: an `enum` (`driver_metric`) specifying the metric responsible for driving the evolution of an `Experiment`'s `Genus`.
  fitness_threshold: a `double` specifying the fitness threshold for `Organism`s' `Graph`s to be stored.
  novelty_threshold: a `double` specifying the novelty threshold for `Organism`s' behaviors to be stored.
  novelty_neighbors: an `integer` specifying the number of nearest neighbors to be considered when assessing an `Organism`'s novelty.
  novelty_threshold_modifiers: a `std::vector<double>` specifying the factors by which the novelty threshold should decrease and increase.
  generational_cycles: an `integer` specifying the number of generational cycles for which an `Experiment` will run.
  population_size: an `integer` specifying the number of `Organism`s in an `Experiment`'s `Genus`.
  mutation_attempts: an `integer` specifying the number of attempts at mutating a `Genotype`.
  spawning_attempts: an `integer` specifying the number of attempts at producing an offspring `Organism`.
  weight_bound: a `double` specifying the bounding value for the generation and replacement of `Link` weights.
  perturbation_power: a `double` specifying the perturbation power when altering `Link` weights.
  initial_activation: an `enum` (`node_activation`) specifying the activation a new HIDDEN `Node` is initially equipped with.
  rejection_fraction: a `double` specifying the fraction of `Organism`s to be rejected at a given evolution cycle.
  stagnation_threshold: an `integer` specifying the number of evolution cycles beyond which a stagnated `Species` can be discarded.
  compatibility_threshold: a `double` specifying the degree of similarity beyond which `Organism`s group in separate `Species`.
  compatibility_weights: a `std::vector<double>` specifying the relevance of matching, disjoint, and excess `Link`s when comparing `Genotype`s.
  enabling_link: a `std::vector<double>` encapsulating the P.M.F. for enabling of a random DISABLED `Link`.
  altering_links: a `std::vector<double>` encapsulating the P.M.F. for altering each ENABLED `Link`.
  altering_weight: a `std::vector<double>` encapsulating the P.M.F. for altering a `Link`'s weight.
  adding_link: a `std::vector<double>` encapsulating the P.M.F. for adding a `Link` of a given role.
  enabling_node: a `std::vector<double>` encapsulating the P.M.F. for enabling a DISABLED INPUT `Node` and connecting it to another `Node` of a given role.
  altering_nodes: a `std::vector<double>` encapsulating the P.M.F. for altering each HIDDEN `Node`.
  altering_activation: a `std::vector<double>` encapsulating the P.M.F. for altering a `Node`'s activation.
  adding_node: a `std::vector<double>` encapsulating the P.M.F. for adding a `Node` by splitting a `Link` of a given role.
  assimilating_links: a `std::vector<double>` encapsulating the P.M.F. for assimilating each homologous `Link`.
  assimilating_nodes: a `std::vector<double>` encapsulating the P.M.F. for assimilating each homologous `Node`.
  assimilating_weight: a `std::vector<double>` encapsulating the P.M.F. for assimilating a homologous `Link`'s weight.
  assimilating_activation: a `std::vector<double>` encapsulating the P.M.F. for assimilating a homologous `Node`'s activation.
  spawning_organism: a `std::vector<double>` encapsulating the P.M.F. for spawning a new `Organism` through a given process.

  Constructor:
  -----------
  default: initializes this `Parameters` instance.
 
  Destructor:
  ----------
  default: deletes this `Parameters` instance.
*/

/*
  Contributors: Fernando Zago.
*/

#pragma once

#include <vector>
#include "../neatnik/neatnik.hpp"

class Parameters
{
public:

    // Data:

    // The metric responsible for driving the evolution of an `Experiment`'s `Genus`.
    static driver_metric evolution_driver;

    // Fitness threshold for `Organism`s' `Graph`s to be stored.
    static double fitness_threshold;

    // Novelty threshold for `Organism`s' behaviors to be stored.
    static double novelty_threshold;

    // Number of nearest neighbors to be considered when assessing an `Organism`'s novelty.
    static int novelty_neighbors;

    // The factors by which the novelty threshold should decrease and increase.
    static std::vector<double> novelty_threshold_modifiers;

    // Number of generational cycles for which an `Experiment` will run.
    static int generational_cycles;

    // Number of `Organism`s in an `Experiment`'s `Genus`.
    static int population_size;

    // Number of attempts at mutating a `Genotype`.
    static int mutation_attempts;

    // Number of attempts at producing an offspring `Organism`.
    static int spawning_attempts;

    // Bounding value for the generation and replacement of `Link` weights.
    static double weight_bound;

    // Perturbation power when altering `Link` weights.
    static double perturbation_power;

    // The activation a new HIDDEN `Node` is initially equipped with.
    static node_activation initial_activation;

    // Fraction of rejected `Organism`s at a given evolution cycle.
    static double rejection_fraction;

    // Number of evolution cycles beyond which a stagnated `Species` can be discarded.
    static int stagnation_threshold;

    // The degree of similarity beyond which `Organism`s group in separate `Species`.
    static double compatibility_threshold;

    // Relevance of matching, disjoint, and excess `Link`s when comparing `Genotype`s.
    static std::vector<double> compatibility_weights;

    // P.M.F. for enabling of a random DISABLED `Link`: {FAILURE, SUCCESS}.
    static std::vector<double> enabling_link;

    // P.M.F. for altering each ENABLED `Link`: {FAILURE, SUCCESS}.
    static std::vector<double> altering_links;

    // P.M.F. for altering a `Link`'s weight: {FAILURE, PERTURB, REPLACE}.
    static std::vector<double> altering_weight;

    // P.M.F. for adding a `Link` of a given role: {FAILURE, FORWARD, RECURRENT, BIASING, LOOPED}.
    static std::vector<double> adding_link;

    // P.M.F. for enabling a DISABLED INPUT `Node` and connecting it to another `Node` of a given role: {FAILURE, HIDDEN, OUTPUT}.
    static std::vector<double> enabling_node;

    // P.M.F. for altering each HIDDEN `Node`: {FAILURE, SUCCESS}.
    static std::vector<double> altering_nodes;

    // P.M.F. for altering a `Node`'s activation: {FAILURE, HEAVISIDE, RELU, LOGISTIC}.
    static std::vector<double> altering_activation;

    // P.M.F. for adding a `Node` by splitting a `Link` of a given role: {FAILURE, FORWARD, RECURRENT}.
    static std::vector<double> adding_node;

    // P.M.F. for assimilating each homologous `Link`: {FAILURE, SUCCESS}.
    static std::vector<double> assimilating_links;

    // P.M.F. for assimilating each homologous `Node`: {FAILURE, SUCCESS}.
    static std::vector<double> assimilating_nodes;

    // P.M.F. for assimilating a homologous `Link`'s weight: {FAILURE, SUCCESS}.
    static std::vector<double> assimilating_weight;

    // P.M.F. for assimilating a homologous `Node`'s activation: {FAILURE, SUCCESS}.
    static std::vector<double> assimilating_activation;

    // P.M.F. for spawning a new `Organism` through a given process: {MUTATION, ASSIMILATION}.
    static std::vector<double> spawning_organism;


    // Constructor:

    // Default constructor responsible for initializing this `Parameters` instance.
    Parameters();


    // Destructor:

    // Default destructor responsible for deleting this `Parameters` instance.
    ~Parameters();
};
