/*
  A `Genotype` stores and manipulates the genetic make-up of an `Organism`.

  Data:
  ----
  links: a `Chromosome<Link>*` encoding the `Link`s which make up this `Genotype`.
  nodes: a `Chromosome<Node>*` encoding the `Node`s which make up this `Genotype`.

  Constructors:
  ------------
  minimal fully-connected: constructs a fully-connected `Genotype` containing no HIDDEN `Node`s.
  copy: makes a deep copy of the input `Genotype`.

  Destructor:
  ----------
  recursive: deletes this `Genotype` and its `Chromosome`s.

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
*/

/*
  Contributors: Fernando Zago and Hans Hopkins.
*/

#pragma once

#include <utility>
#include <unordered_set>
#include <algorithm>
#include <numeric>
#include "../main/main.h"
#include "../utils/utils.h"
#include "../elements/elements.h"
#include "../genotype/chromosome.cpp"
#include "../organism/organism.h"
#include "../genus/genus.h"


// Defines a `Genotype`.
class Genotype
{
public:

    // Data:

    // Pointer to the `Organism` associated with this `Genotype`.
    Organism* organism;

    // `Chromosome<E>*`s encoding the `E`s which make up this `Genotype`.
    Chromosome<Link>* links;
    Chromosome<Node>* nodes;


    // Constructor:
    // TODO: Add more options for `Genotype` initialization.

    // Minimal fully-connected constructor.
    Genotype(Organism* thatOrganism_, Archetype thatArchetype_);

    // Copy constructor responsible for making a deep copy of the input `Genotype`.
    Genotype(Organism* thatOrganism_, Genotype* thatGenotype_);


    // Destructor:

    // Recursive destructor.
    ~Genotype();


    // Methods:

    // Retrieves the total number of `Link`s and `Node`s encoded by this `Genotype`.
    int size();

    // Searches for a `Link` or `Node` with matching bounding identification tags.
    bool contain(int role_, element_type type_, unsigned int in_tag_, unsigned int out_tag_);

    // Encodes a new `Link` into this `Genotype`.
    Link* encode(link_role role_, element_type type_, Node* inNode_, Node* outNode_, double weight_);

    // Encodes a new `Node` into this `Genotype`.
    Node* encode(node_role role_, element_type type_, Node* inNode_, Node* outNode_, activation function_);

    // Encodes a new `Node` into this `Genotype`.
    Node* encode(element_state state_, node_role role_, element_type type_, activation function_, int x_, int y_);

    // Mutates this `Genotype`.
    // TODO: Make it possible to set the rate at which structural and parameter mutations occur.
    void mutate();

    // Enables a DISABLED `Link` belonging to this `Genotype`.
    void enable_link();

    // Attempts to alter the weights of each ENABLED `Link` belonging to this `Genotype`.
    // TODO: Make the alterations more likely for newer `Link`s, leaving the older and more time-tested ones relatively unaltered.
    void alter_links();

    // Attempts to add a new `Link` to this `Genotype`.
    void add_link(link_role role_, int attempts_ = mutation_attempts);

    // Enables a DISABLED INPUT `Node` belonging to this `Genotype`.
    void enable_node();

    // Attempts to alter the activation function of each ENABLED HIDDEN `Node` belonging to this `Genotype`.
    // TODO: Make the alterations more likely for newer `Node`s, leaving the older and more time-tested ones relatively unaltered.
    void alter_nodes();

    // Attempts to add a new HIDDEN `Node` to this `Genotype`.
    // TODO: Make the splitting of newer `Link`s less likely, avoiding deleterious chain splittings in young `Organisms`.
    void add_node(link_role role_, int attempts_ = mutation_attempts);

    // Assimilates the homologous `Link`s and `Node`s belonging to the input `Genotype`.
    // TODO: Make it so that `Genotype`s can also fuse during crossover.
    void assimilate(Genotype* thatGenotype_);

    // Attempts to assimilate each homologous `Link` belonging to the input `Chromosome`.
    void assimilate_links(Chromosome<Link>* thatChromosome_);

    // Attempts to assimilate each homologous `Node` belonging to the input `Chromosome`.
    void assimilate_nodes(Chromosome<Node>* thatChromosome_);

    // Computes the degree of compatibility with the input `Genotype`.
    double compatibility(Genotype* thatGenotype_);
};
