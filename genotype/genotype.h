/*
  A `Genotype` stores and manipulates the genetic make-up of an `Organism`.

  Data:
  ----
  organism: the `Organism*` associated with this `Genotype`.
  parameters: the `Parameters*` responsible for shaping this `Genotype`'s development.
  links: a `Chromosome<Link>*` encoding the `Link`s which make up this `Genotype`.
  nodes: a `Chromosome<Node>*` encoding the `Node`s which make up this `Genotype`.

  Constructors:
  ------------
  initialization: initializes this `Genotype` from a minimal `Graph`.
  copy: makes a deep copy of the input `Genotype`.
  replication: replicates a `Genotype` from its associated `Graph`.

  Destructor:
  ----------
  recursive: recursively deletes this `Genotype` and its `Chromosome`s.

  Methods:
  -------
  size: retrieves the total number of `Link`s and `Node`s encoded by this `Genotype`.
  contain: searches for a `Link` or `Node` with matching bounding identification tags.
  encode: encodes a new `Link` or `Node` into this `Genotype`.
  mutate: alters and/or adds new `Link`s and `Node`s to this `Genotype`.
  enable_link: enables a DISABLED `Link` belonging to this `Genotype`.
  alter_links: attempts to alter the weight of each ENABLED `Link` belonging to this `Genotype`.
  add_link: attempts to add a new `Link` into this `Genotype`.
  enable_node: enables a DISABLED INPUT `Node` belonging to this `Genotype`.
  alter_nodes: attempts to alter the activation function of each ENABLED HIDDEN `Node` belonging to this `Genotype`.
  add_node: attempts to add a new HIDDEN `Node` into this `Genotype`.
  assimilate: assimilates the homologous `Link`s and `Node`s belonging to the input `Genotype`.
  assimilate_links: attempts to assimilate each homologous `Link` belonging to the input `Chromosome`.
  assimilate_nodes: attempts to assimilate each homologous `Node` belonging to the input `Chromosome`.
  compatibility: computes the degree of compatibility with the input `Genotype`.
  graph: produces this `Genotype`'s associated `Graph`.
*/

/*
  Contributors: Fernando Zago and Hans Hopkins.
*/

#pragma once

#include <pybind11/pybind11.h>
#include <utility>
#include <optional>
#include <unordered_set>
#include <algorithm>
#include <numeric>
#include "../neatnik/neatnik.h"
#include "../utils/utils.h"
#include "../elements/elements.h"
#include "../genotype/chromosome.cpp"
#include "../organism/organism.h"
#include "../genus/genus.h"
#include "../experiment/parameters.h"
#include "../experiment/experiment.h"

class Genotype
{
public:

    // Data:

    // The `Organism*` associated with this `Genotype`.
    Organism* organism;

    // The `Parameters*` responsible for shaping this `Genotype`'s development.
    Parameters* parameters;

    // `Chromosome<E>*`s encoding the `E`s which make up this `Genotype`.
    Chromosome<Link>* links;
    Chromosome<Node>* nodes;


    // Constructors:
    // TODO: Add more options for `Genotype` initialization.

    // Constructor responsible for initializing this `Genotype` from a minimal `Graph`.
    Genotype(Organism* thatOrganism_, Graph thatGraph_);

    // Copy constructor responsible for making a deep copy of the input `Genotype`.
    Genotype(Organism* thatOrganism_, Genotype* thatGenotype_);

    // Constructor responsible for replicating a `Genotype` from its associated `Graph`.
    Genotype(Graph thatGraph_);


    // Destructor:

    // Destructor responsible for recursively deleting this `Genotype` and its `Chromosome`s.
    ~Genotype();


    // Methods:

    // Retrieves the total number of `Link`s and `Node`s encoded by this `Genotype`.
    int size();

    // Searches for a `Link` or `Node` with matching bounding identification tags.
    bool contain(int role_, element_type type_, unsigned int in_tag_, unsigned int out_tag_);

    // Encodes a new `Link` into this `Genotype`.
    Link* encode(link_role role_, element_type type_, Node* inNode_, Node* outNode_, double weight_);

    // Encodes a new `Node` into this `Genotype`.
    Node* encode(node_role role_, element_type type_, Node* inNode_, Node* outNode_, node_activation activation_);

    // Encodes a new `Node` into this `Genotype`.
    Node* encode(element_state state_, node_role role_, element_type type_, node_activation activation_, int x_, int y_);

    // Mutates this `Genotype`.
    // TODO: Make it possible to set the rate at which structural and parameter mutations occur.
    void mutate();

    // Enables a DISABLED `Link` belonging to this `Genotype`.
    void enable_link();

    // Attempts to alter the weights of each ENABLED `Link` belonging to this `Genotype`.
    // TODO: Make the alterations more likely for newer `Link`s, leaving the older and more time-tested ones relatively unaltered.
    void alter_links();

    // Attempts to add a new `Link` to this `Genotype`.
    void add_link(link_role role_);

    // Enables a DISABLED INPUT `Node` belonging to this `Genotype`.
    void enable_node(node_role role_);

    // Attempts to alter the activation function of each ENABLED HIDDEN `Node` belonging to this `Genotype`.
    // TODO: Make the alterations more likely for newer `Node`s, leaving the older and more time-tested ones relatively unaltered.
    void alter_nodes();

    // Attempts to add a new HIDDEN `Node` to this `Genotype`.
    // TODO: Make the splitting of newer `Link`s less likely, avoiding deleterious chain splittings in young `Organism`s.
    void add_node(link_role role_);

    // Assimilates the homologous `Link`s and `Node`s belonging to the input `Genotype`.
    // TODO: Make it so that `Genotype`s can also fuse during crossover.
    void assimilate(Genotype* thatGenotype_);

    // Attempts to assimilate each homologous `Link` belonging to the input `Chromosome`.
    void assimilate_links(Chromosome<Link>* thatChromosome_);

    // Attempts to assimilate each homologous `Node` belonging to the input `Chromosome`.
    void assimilate_nodes(Chromosome<Node>* thatChromosome_);

    // Computes the degree of compatibility with the input `Genotype`.
    double compatibility(Genotype* thatGenotype_);

    // Produces this `Genotype`'s associated `Graph`.
    Graph graph();
};
