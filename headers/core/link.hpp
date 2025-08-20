/*
  Contributors: Fernando Zago.
*/

#pragma once

#include <cstdint>
#include <tuple>
#include "neatnik.hpp"


class Link
{
public:

    // Properties:

    Key key;

    std::uint32_t tag;

    element_state state;

    link_role role;

    Node* source = nullptr;
    Node* target = nullptr;

    double weight;


    // Constructors:

    Link(Key key_, std::uint32_t tag_, element_state state_, link_role role_, Node* source_, Node* target_, double weight_);

    Link(Link* link_);


    // Methods:

    void engage();

    LinkData data();
};
