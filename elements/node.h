/*
  A `Node` is an individual processing unit which receives and broadcasts signals through its input and output `Link`s, respectively.

  Data:
  ----
  tag: an `unsigned integer` specifying this `Node`'s identity within a `Population`.
  element_state: an `enum` (`element_state`) which specifies whether this `Node` is active.
  role: an `enum` (`link_role`) labeling this `Node`'s role in the artificial neural network.
  inLinks: a `std::vector<Link*>` encoding this `Node`'s incoming `Link`s.
  outLinks: a `std::vector<Link*>` encoding this `Node`'s outgoing `Link`s.
  inputs: a `std::vector<double>` containing the external weighted signals arriving at this `Node`.
  output: a `double` containing the last output signal generated by this `Node`.
  activation: a pointer to this this `Node`'s activation function.
  x: a `double` specifying this `Node`'s horizontal coordinate.
  y: a `double` specifying this `Node`'s vertical coordinate.

  Constructors:
  ------------
  complete: creates a `Node` instance by specifying all of its non-dynamic data.
  split: initializes a new `Node` instance placed half-way between two other `Node`s.
  copy: makes a shallow copy of the input `Node`.

  Methods:
  -------
  engage: prompts this `Node` to produce and broadcast an output signal.
  disengage: primes this `Node` for a subsequent engagement.
  assimilate: makes this `Node` assimilate another `Node`'s activation function.

  Operators:
  ---------
  <: compares the innovation tags of two `Node`s.
  ==: checks whether two `Node`s possess the same identification tag
*/

/*
  Contributors: Fernando Zago.
*/

#pragma once

#include <vector>
#include "../neatnik/neatnik.h"


// Defines a `Node`.
class Node
{
public:

    // Data:

    // A unique label specifying this `Link`'s identity within a `Population`.
    unsigned int tag;

    // Control flag which specifies whether this `Node` is ENABLED or DISABLED.
    element_state state;

    // Establishes whether the instance operates as an INPUT, HIDDEN, BIAS, or OUTPUT `Node`.
    node_role role;

    // Vectors containing all of this `Node`'s incoming and outgoing `Link*`s.
    std::vector<Link*> inLinks {NULL};
    std::vector<Link*> outLinks;

    // The external weighted signals arriving at this `Node`, and its last generated output.
    std::vector<double> inputs;
    double output = 0;

    // This `Node`'s activation function.
    activation function;

    // This `Node`'s coordinates.
    double x, y;


    // Constructors:

    // Complete constructor for which all non-dynamic data specifying the `Node` is provided.
    Node(unsigned int tag_, element_state state_, node_role role_, activation function_, double x_, double y_);

    // Split constructor resposible for initializing a new `Node` instance placed half-way between two other `Node`s.
    Node(unsigned int tag_, element_state state_, node_role role_, Node* inNode_, Node* outNode_, activation function_);

    // Copy constructor responsible for making a shallow copy of the input `Node`.
    Node(Node* thatNode_);


    // Methods:

    // Prompts this `Node` to produce and broadcast a new output signal.
    void engage();

    // Primes this `Node` for a subsequent engagement.
    void disengage();

    // Makes this `Node` assimilate another `Node`'s activation function.
    void assimilate(Node* thatNode_);


    // Operators:

    // Overloaded '<' operation for comparing two `Node`s' innovation tags.
    bool operator <(const Node& thatNode_) const;

    // Overloaded '==' operation for checking whether two `Node`s possess the same identification tags.
    bool operator ==(const Node& thatNode_) const;
};
