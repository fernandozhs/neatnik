/*
  Contributors: Fernando Zago.
*/

#pragma once

#include <vector>
#include <tuple>
#include <optional>


// Classes:

class Node;

class Link;

template <class E> class Chromosome;

class Genotype;

class Phenotype;

class Organism;

class Species;

class Genus;

class Experiment;

class Parameters;

class PyExperiment;


// Non-Standard Types:

// Labels the two metrics which can be used to drive evolution of a `Genus`.
enum driver_metric {NOVELTY=0, FITNESS=1};

// Labels the two basic constituent elements of an artificial neural network.
enum element_type {NODE=0, LINK=1};

// Labels the two states in which a `Link` or `Node` can be found.
enum element_state {DISABLED=-1, ENABLED=1};

// Labels the possible roles of a `Link` element.
enum link_role {FORWARD=1, RECURRENT=2, BIASING=3, LOOPED=4};

// Labels the possible roles of a `Node` element.
enum node_role {HIDDEN=1, OUTPUT=2, BIAS=3, INPUT=4};

// Labels the possible types of activation a `Node` can be equipped with.
enum node_activation {HEAVISIDE=1, RELU=2, LOGISTIC=3, IDENTITY=4, UNITY=5};

// Labels the possible ways in which a `Link`'s weight can be altered.
enum link_alteration {PERTURBATION=1, REPLACEMENT=2};

// Labels the possible ways in which a new `Organism` can be spawned.
enum spawning_process {MUTATION=0, ASSIMILATION=1};

// Labels the possible groups an `Organism` or a `Species` can belong to within their respective taxons.
enum taxon_group {CONTESTANT=0, DOMINANT=1};


// Aliases:

// The data required for (re)constructing a `Link`.
using Edge = std::tuple<std::optional<unsigned long int>, std::optional<unsigned int>, element_state, link_role, unsigned long int, unsigned long int, std::optional<double>>;

// The data required for (re)constructing a `Node`.
using Vertex = std::tuple<unsigned long int, std::optional<unsigned int>, element_state, node_role, node_activation, double, double>;

// The data required for (re)constructing a `Genotype`.
using Graph = std::tuple<std::vector<Vertex>, std::vector<Edge>>;
