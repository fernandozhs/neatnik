/*
  A `Link` relays signals between the two `Node`s it connects.

  Data:
  ----
  innovation: an `Innovation*` specifying this `Link`'s identity within a `Population`.
  element_state: an `enum` (`element_state`) which specifies whether this `Link` is active.
  role: an `enum` (`link_role`) labeling this `Link`'s role in the artificial neural network.
  inNode: the `Node*` from which this `Link`'s input signal originates.
  outNode: the `Node*` to which this `Link`'s ouput signal is relayed.
  weight: a `double` which determines the weight affecting the `Link`'s signal.

  Constructors:
  ------------
  complete: creates a `Link` instance by specifying all of its data.
  copy: makes a shallow copy of the input `Link`.

  Methods:
  -------
  engage: prompts this `Link` to relay a signal to and engage its target `Node`.
  assimilate: makes this `Link` assimilate another `Link`'s weight.

  Operators:
  ---------
  <: compares the identification tags of two `Link`s.
  ==: checks whether two `Link`s possess the same identification tag.
*/

/*
  Contributors: Fernando Zago.
*/

#pragma once

#include "../neatnik/neatnik.h"
#include "../innovation/innovation.h"


// Defines a `Link`.
class Link
{
public:

    // Data:

    // A unique label specifying this `Link`'s identity within a `Population`.
    Innovation* innovation;

    // Control flag which specifies whether this `Link` is ENABLED or DISABLED.
    element_state state;

    // Establishes whether this instance behaves as a FORWARD, BIASING, RECURRENT or LOOPED `Link`.
    link_role role;

    // The source and target `Node`s connected by this `Link`.
    Node* inNode;
    Node* outNode;

    // The weight by which the signal originated in the source `Node` is multiplied by before being transmitted to the target `Node`.
    double weight;


    // Constructors:

    // Complete constructor for which all data specifying the `Link` is provided.
    Link(Innovation* innovation_, element_state state_, link_role role_, Node* inNode_, Node* outNode_, double weight_);

    // Copy constructor responsible for making a shallow copy of the input `Link`.
    Link(Link* thatLink_);


    // Methods:

    // Prompts this `Link` to relay a signal to and engage its target `Node`.
    void engage();

    // Makes this `Link` assimilate another `Link`'s weight.
    void assimilate(Link* thatLink_);


    // Operators:

    // Overloaded '<' operation for comparing two `Link`s' identification tags.
    bool operator <(const Link& thatLink_) const;

    // Overloaded '==' operation for checking whether two `Link`s possess the same identification tags.
    bool operator ==(const Link& thatLink_) const;
};
