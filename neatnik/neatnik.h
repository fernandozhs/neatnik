/*
  NEATnik.
*/

#pragma once

#include <vector>
#include <tuple>
#include <optional>


/*
  Classes:
  -------
*/

// Base classes:
class Node;
class Link;

// Genotypical classes:
template <class E> class Chromosome;
class Genotype;

// Phenotypical class:
class Phenotype;

// Evolutionary classes:
class Organism;
class Species;
class Genus;
class Experiment;

// Auxiliary class:
class PyExperiment;


/*
  Non-Standard Types:
  ------------ -----
*/

// Labels the two basic constituent elements of an artificial neural network.
enum element_type {NODE=0, LINK=1};

// Labels the two states in which a `Link` or `Node` can be found.
enum element_state {DISABLED=-1, ENABLED=1};

// Labels the possible roles of a `Link` element.
enum link_role {FORWARD=1, RECURRENT=2, BIASING=3, LOOPED=4};

// Labels the possible roles of a `Node` element.
enum node_role {INPUT=1, HIDDEN=2, BIAS=3, OUTPUT=4};

// Labels the possible types of activation a `Node` can be equipped with.
enum node_activation {HEAVISIDE=1, RELU=2, LOGISTIC=3, IDENTITY=4};

// Labels the possible ways in which a `Link`'s weight can be altered.
enum link_alteration {PERTURB=1, REPLACE=2};

// Labels the possible ways in which a new `Organism` can be spawned.
enum spawning_process {MUTATION=0, ASSIMILATION=1};

// Labels the possible groups an `Organism` or a `Species` can belong to within their respective taxons.
enum taxon_group {CONTESTANT=0, DOMINANT=1};


/*
  Aliases:
  -------
*/

// The data required for (re)constructing a `Link`.
using Edge = std::tuple<std::optional<unsigned long int>, std::optional<unsigned int>, element_state, link_role, unsigned long int, unsigned long int, std::optional<double>>;

// The data required for (re)constructing a `Node`.
using Vertex = std::tuple<unsigned long int, std::optional<unsigned int>, element_state, node_role, node_activation, double, double>;

// The data required for (re)constructing a `Genotype`.
using Graph = std::tuple<std::vector<Vertex>, std::vector<Edge>>;


/*
  General Parameters:
  ------- ----------
*/

// Number of generational cycles for which an `Experiment` will run.
extern int generational_cycles;

// Number of `Organism`s in an `Experiment`'s `Genus`.
extern int population_size;

// Number of attempts at mutating a `Genotype`.
extern int mutation_attempts;

// Number of attempts at spawning a new `Organism`.
extern int spawning_attempts;

// Bounding value for `Link` weights.
extern double weight_bound;

// Perturbation power when altering `Link` weights.
extern double perturbation_power;

// Relevance of matching, disjoint, and excess `Link`s when comparing `Genotype`s.
extern std::vector<double> compatibility_weights;

// Fraction of rejected `Organism`s at a given evolution cycle.
extern double rejection_fraction;

// Number of evolution cycles beyond which a stagnated `Species` can be discarded.
extern int stagnation_threshold;

// The degree of similarity beyond which `Organism`s group in separate `Species`.
extern double compatibility_threshold;


/*
  Probability Mass Functions:
  ----------- ---- ---------
*/

// P.M.F. for enabling of a random DISABLED `Link`: {FAILURE, SUCCESS}.
extern std::vector<double> enabling_link;

// P.M.F. for altering each ENABLED `Link`: {FAILURE, SUCCESS}.
extern std::vector<double> altering_links;

// P.M.F. for altering a `Link`'s weight: {FAILURE, PERTURB, REPLACE}.
extern std::vector<double> altering_weight;

// P.M.F. for adding a `Link` of a given role: {FAILURE, FORWARD, RECURRENT, BIASING, LOOPED}.
extern std::vector<double> adding_link;

// P.M.F. for enabling a DISABLED INPUT `Node`: {FAILURE, SUCCESS}.
extern std::vector<double> enabling_node;

// P.M.F. for altering each HIDDEN `Node`: {FAILURE, SUCCESS}.
extern std::vector<double> altering_nodes;

// P.M.F. for altering a `Node`'s activation: {FAILURE, HEAVISIDE, RELU, LOGISTIC}.
extern std::vector<double> altering_activation;

// P.M.F. for adding a `Node` by splitting a `Link` of a given role: {FAILURE, FORWARD, RECURRENT}.
extern std::vector<double> adding_node;

// P.M.F. for assimilating each homologous `Link`: {FAILURE, SUCCESS}.
extern std::vector<double> assimilating_links;

// P.M.F. for assimilating each homologous `Node`: {FAILURE, SUCCESS}.
extern std::vector<double> assimilating_nodes;

// P.M.F. for assimilating a homologous `Link`'s weight: {FAILURE, SUCCESS}.
extern std::vector<double> assimilating_weight;

// P.M.F. for assimilating a homologous `Node`'s activation function: {FAILURE, SUCCESS}.
extern std::vector<double> assimilating_function;

// P.M.F. for spawning a new `Organism` through a given process: {MUTATION, ASSIMILATION}.
extern std::vector<double> spawning_organism;
