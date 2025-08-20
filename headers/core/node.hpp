/*
  Contributors: Fernando Zago.
*/

#pragma once

#include <cstdint>
#include <vector>
#include <tuple>
#include "utilities.hpp"
#include "neatnik.hpp"


class Node
{
public:

    // Properties:

    Key key;

    std::uint32_t tag;

    element_state state;

    node_role role;

    std::vector<Link*> incoming {nullptr};
    std::vector<Link*> outgoing;

    std::vector<double> inputs;
    double output = 0;

    node_activation activation;

    double x, y;


    // Constructors:

    Node(Key key_, std::uint32_t tag_, element_state state_, node_role role_, node_activation activation_, std::uint32_t x_, std::uint32_t y_);

    Node(Key key_, std::uint32_t tag_, element_state state_, node_role role_, Node* source_, Node* target_, node_activation activation_);

    Node(Node* node_);


    // Methods:

    double activate();

    void engage();

    void disengage();

    void clear();

    NodeData data();
};
