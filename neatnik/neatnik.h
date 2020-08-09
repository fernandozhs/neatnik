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

// Basic classes and data structures: `Node`, `Link`, and `Innovation`.
class Node;
class Link;
struct Innovation;

// Genotypical classes: `Chromosome` and `Genotype`.
template <class E> class Chromosome;
class Genotype;

// Phenotypical class: `Phenotype`.
class Phenotype;

// Evolutionary classes: `Organism` and `Population`.
class Organism;
class Population;


/*
  Non-Standard Types:
  ------------ -----
*/

// Labels the two possible types of `Phenotype` elements.
enum element_type {NODE=0, LINK=1};

// Labels the two states in which a `Phenotype` element can be found.
enum element_state {DISABLED=-1, ENABLED=1};

// Labels the possible roles of a `Link` element.
enum link_role {FORWARD=1, BIASING=2, RECURRENT=3, LOOPED=4};

// Labels the possible roles of a `Node` element.
enum node_role {INPUT=1, BIAS=2, HIDDEN=3, OUTPUT=4};

// A `Node`'s activation function.
typedef double (*activation)(std::vector<double>&);

// A `Genotype`'s archetype.
typedef std::vector<std::tuple<element_state, node_role, activation, double, double>> Archetype;

// Labels the possible ways in which a `Link`'s weight can be altered.
enum link_alterations {PERTURB=1, REPLACE=2};

// Labels the possible activation functions a HIDDEN `Node` can be equipped with.
enum activation_functions {HEAVISIDE=1, RELU=2, LOGISTIC=3};


/*
  Parameters:
  ----------
*/

// Number of attempts at mutating a `Genotype`.
extern int attempts;

// Bounding value for `Link` weights.
extern double bound;

// Perturbation power when altering `Link` weights.
extern double power;


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

// P.M.F. for adding a `Link` of a given role: {FAILURE, FORWARD, BIASING, RECURRENT, LOOPED}.
extern std::vector<double> adding_link;

// P.M.F. for enabling a DISABLED INPUT `Node`: {FAILURE, SUCCESS}.
extern std::vector<double> enabling_node;

// P.M.F. for altering each HIDDEN `Node`: {FAILURE, SUCCESS}.
extern std::vector<double> altering_nodes;

// P.M.F. for altering a `Node`'s activation function: {FAILURE, HEAVISIDE, RELU, LOGISTIC}.
extern std::vector<double> altering_function;

// P.M.F. for adding a `Node` by splitting a `Link` of given role: {FAILURE, FORWARD, RECURRENT}.
extern std::vector<double> adding_node;

// P.M.F. for assimilating a `Link` or `Node` during crossover: {FAILURE, SUCCESS}
extern std::vector<double> assimilating_element;
