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
#include "../neatnik/neatnik.hpp"
#include "../utils/utils.hpp"
#include "../elements/elements.hpp"
#include "../genotype/chromosome.cpp"
#include "../organism/organism.hpp"
#include "../genus/genus.hpp"
#include "../experiment/parameters.hpp"
#include "../experiment/experiment.hpp"

class Genotype
{
public:

    // Properties:

    Organism* organism;

    Chromosome<Link>* links;
    Chromosome<Node>* nodes;


    // Constructors:

    Genotype(Organism* organism_, Graph graph_);

    Genotype(Organism* organism_, Genotype* genotype_);

    Genotype(Graph graph_);


    // Destructor:

    ~Genotype();


    // Methods:

    int size();

    bool contain(int role_, element_type type_, unsigned int source_tag_, unsigned int target_tag_);

    Link* encode(link_role role_, element_type type_, Node* source_, Node* target_, double weight_);

    Node* encode(node_role role_, element_type type_, Node* source_, Node* target_, node_activation activation_);

    Node* encode(element_state state_, node_role role_, element_type type_, node_activation activation_, int x_, int y_);

    void mutate();

    void enable_link();

    void alter_links();

    void add_link(link_role role_);

    void enable_node(node_role role_);

    void alter_nodes();

    void add_node(link_role role_);

    void assimilate(Genotype* genotype_);

    void assimilate_links(Chromosome<Link>* chromosome_);

    void assimilate_nodes(Chromosome<Node>* chromosome_);

    double compatibility(Genotype* genotype_);

    Graph graph();
};
