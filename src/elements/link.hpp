/*
  Contributors: Fernando Zago.
*/

#pragma once

#include <tuple>
#include "../neatnik/neatnik.hpp"

class Link
{
public:

    // Properties:

    unsigned long int key;

    unsigned int tag;

    element_state state;

    link_role role;

    Node* source = nullptr;
    Node* target = nullptr;

    double weight;


    // Constructors:

    Link(unsigned long int key_, unsigned int tag_, element_state state_, link_role role_, Node* source_, Node* target_, double weight_);

    Link(Link* link_);


    // Methods:

    void engage();

    Edge graph();
};
