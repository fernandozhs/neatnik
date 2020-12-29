/*
  A `Node` is an individual processing unit which receives and broadcasts signals through its input and output `Link`s, respectively.

  Data:
  ----
  key: a unique `unsigned long int` specifying this `Node`'s relative position within the artificial neural network.
  tag: an `unsigned int` specifying this `Node`'s identity within a `Genus`.
  element_state: an `enum` (`element_state`) which specifies whether this `Node` is active.
  role: an `enum` (`link_role`) labeling this `Node`'s role in the artificial neural network.
  inLinks: a `std::vector<Link*>` encoding this `Node`'s incoming `Link`s.
  outLinks: a `std::vector<Link*>` encoding this `Node`'s outgoing `Link`s.
  inputs: a `std::vector<double>` containing the external weighted signals arriving at this `Node`.
  output: a `double` containing the last output signal generated by this `Node`.
  activation: an `enum` (`node_activation`) which specifies this `Node`'s activation function.
  x: a `double` specifying this `Node`'s horizontal coordinate.
  y: a `double` specifying this `Node`'s vertical coordinate.

  Constructors:
  ------------
  complete: creates a `Node` by specifying all of its non-dynamic data.
  split: initializes a new `Node` located half-way between two other `Node`s.
  copy: makes a shallow copy of the input `Node`.

  Methods:
  -------
  activate: produces this `Node`'s output signal.
  engage: prompts this `Node` to produce and broadcast an output signal.
  disengage: primes this `Node` for a subsequent engagement.
  graph: produces this `Node`'s associated `Graph` `Vertex`.
*/

/*
  Contributors: Fernando Zago.
*/

#pragma once

#include <vector>
#include <tuple>
#include "../utils/utils.h"
#include "../neatnik/neatnik.h"


// Defines a `Node`.
class Node
{
public:

    // Data:

    // A unique label specifying specifying this `Node`'s relative position within the artificial neural network.
    unsigned long int key;

    // A unique label specifying this `Link`'s identity within a `Genus`.
    unsigned int tag;

    // Control flag which specifies whether this `Node` is ENABLED or DISABLED.
    element_state state;

    // Establishes whether this instance operates as an INPUT, HIDDEN, BIAS, or OUTPUT `Node`.
    node_role role;

    // Vectors containing all of this `Node`'s incoming and outgoing `Link*`s.
    std::vector<Link*> inLinks {nullptr};
    std::vector<Link*> outLinks;

    // The external weighted signals arriving at this `Node`, and its last generated output.
    std::vector<double> inputs;
    double output = 0;

    // Specifies whether this `Node`'s activation corresponds to the HEAVISIDE, RELU, LOGISTIC, or IDENTITY function.
    node_activation activation;

    // This `Node`'s coordinates.
    double x, y;


    // Constructors:

    // Complete constructor for which all non-dynamic data specifying the `Node` is provided.
    Node(unsigned long int key_, unsigned int tag_, element_state state_, node_role role_, node_activation activation_, double x_, double y_);

    // Split constructor resposible for initializing a new `Node` located half-way between two other `Node`s.
    Node(unsigned long int key_, unsigned int tag_, element_state state_, node_role role_, Node* inNode_, Node* outNode_, node_activation activation_);

    // Copy constructor responsible for making a shallow copy of the input `Node`.
    Node(Node* thatNode_);


    // Methods:

    // Produces this `Node`'s output signal.
    double activate();

    // Prompts this `Node` to produce and broadcast a new output signal.
    void engage();

    // Primes this `Node` for a subsequent engagement.
    void disengage();

    // Produces this `Node`'s associated `Graph` `Vertex`.
    Vertex graph();
};
