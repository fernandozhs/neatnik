/*
NEATnik.
*/

#pragma once

#include <vector>
#include <tuple>


/*
  Data Structures and Classes:
  ---- ---------- --- -------
*/

// Base classes: `Node` and `Link`.
class Node;
class Link;

// Genotypical classes: `Chromosome` and `Genotype`.
template <class E> class Chromosome;
class Genotype;

// Phenotypical class: `Phenotype`.
class Phenotype;

// Evolutionary classes: `Organism`, `Group`, `Species`, `Genus`, and `Experiment`.
class Organism;
template <class O> class Group;
class Species;
class Genus;
class Experiment;

// Control class: `Neatnik`.
class Neatnik;


/*
  Non-Standard Types:
  ------------ -----
*/

// Labels the two possible types of `Phenotype` elements.
enum element_type {NODE=0, LINK=1};

// Labels the two states in which a `Phenotype` element can be found.
enum element_state {DISABLED=-1, ENABLED=1};

// Labels the possible roles of a `Link` element.
enum link_role {FORWARD=1, RECURRENT=2, BIASING=3, LOOPED=4};

// Labels the possible roles of a `Node` element.
enum node_role {INPUT=1, HIDDEN=2, BIAS=3, OUTPUT=4};

// Labels the possible batches an `Organism` or a `Species` can belong to.
enum object_batch {CONTESTANT=0, DOMINANT=1};

// A `Node`'s activation function.
typedef double (*activation)(std::vector<double>&);

// A `Genotype`'s `Archetype`.
typedef std::vector<std::tuple<element_state, node_role, activation, int, int>> Archetype;

// Labels the possible types of activation a HIDDEN `Node` can be equipped with.
enum activation_type {HEAVISIDE=1, RELU=2, LOGISTIC=3, IDENTITY=4};

// Labels the possible ways in which a `Link`'s weight can be altered.
enum link_alteration {PERTURB=1, REPLACE=2};

// Labels the possible ways in which a new `Organism`s can be spawned.
enum spawning_process {MUTATION=0, ASSIMILATION=1};


/*
  Parameters:
  ----------
*/

// Number of evolutions cycles for which the experiment will run.
extern int evolution_cycles;

// Number of `Organism`s in the experiment's `Genus`.
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
extern std::vector<double> altering_function;

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
