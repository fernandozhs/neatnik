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
  encode: encodes a new `Link` or `Node` into this `Genotype`.
  mutate: mutates this `Genotype`.
  enable_link: enables a DISABLED `Link` belonging to this `Genotype`.
  alter_links: attempts to alter the weight of each ENABLED `Link` belonging to this `Genotype`.
  add_link: attempts to add a new `Link` into this `Genotype`.
  enable_node: enables a DISABLED INPUT `Node` belonging to this `Genotype`.
  alter_nodes: attempts to alter the activation function of each ENABLED HIDDEN `Node` belonging to this `Genotype`.
  add_node: attempts to add a new `Node` into this `Genotype`.
  crossover: assimilates another `Genotype` through a crossover operation.
*/

#pragma once

#include <algorithm>
#include "../neatnik/neatnik.h"
#include "../utils/utils.h"
#include "../elements/elements.h"
#include "../genotype/chromosome.cpp"
#include "../organism/organism.h"
#include "../population/population.h"


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

    // Encodes a new `Link` into this `Genotype`.
    void encode(link_role role_, element_type type_, Node* inNode_, Node* outNode_, double weight_);

    // Encodes a new `Node` into this `Genotype`.
    Node* encode(node_role role_, element_type type_, Node* inNode_, Node* outNode_, activation function_);

    // Encodes a new `Node` into this `Genotype`.
    void encode(element_state state_, node_role role_, element_type type_, activation function_, double x_, double y_);

    // Mutates this `Genotype`.
    void mutate();

    // Enables a DISABLED `Link` belonging to this `Genotype`.
    void enable_link();

    // Attempts to alter the weights of each ENABLED `Link` belonging to this `Genotype`.
    // TODO: Make the alterations more likely for newer `Link`s, leaving the older and more time-tested ones relatively unaltered.
    void alter_links();

    // Attempts to add a new `Link` to this `Genotype`.
    void add_link(link_role role_, int attempts_ = attempts);

    // Enables a DISABLED INPUT `Node` belonging to this `Genotype`.
    void enable_node();

    // Attempts to alter the activation function of each ENABLED HIDDEN `Node` belonging to this `Genotype`.
    // TODO: Make the alterations more likely for newer `Node`s, leaving the older and more time-tested ones relatively unaltered.
    void alter_nodes();

    // Attempts to add a new `Node` to this `Genotype`.
    // TODO: Make the splitting of newer `Link`s less likely, avoiding deleterious chain splittings in young `Networks`.
    void add_node(link_role role_, int attempts_ = attempts);

    // Assimilates another `Genotype` through a crossover operation.
    void crossover(Genotype* thatGenotype_);
};
