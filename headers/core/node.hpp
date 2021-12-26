/*
  Contributors: Fernando Zago.
*/

#pragma once

#include <vector>
#include <tuple>
#include "utilities.hpp"
#include "neatnik.hpp"


class Node
{
public:

    // Properties:

    unsigned long int key;

    unsigned int tag;

    element_state state;

    node_role role;

    std::vector<Link*> incoming {nullptr};
    std::vector<Link*> outgoing;

    std::vector<double> inputs;
    double output = 0;

    node_activation activation;

    double x, y;


    // Constructors:

    Node(unsigned long int key_, unsigned int tag_, element_state state_, node_role role_, node_activation activation_, double x_, double y_);

    Node(unsigned long int key_, unsigned int tag_, element_state state_, node_role role_, Node* source_, Node* target_, node_activation activation_);

    Node(Node* node_);


    // Methods:

    double activate();

    void engage();

    void disengage();

    void clear();

    Vertex graph();
};
