/*
  A `Link` relays signals between the two `Node`s it connects.

  Data:
  ----
  key: a unique `unsigned long int` specifying this `Link`'s relative position within the artificial neural network.
  tag: a unique `unsigned int` specifying this `Link`'s identity within a `Genus`.
  element_state: an `enum` (`element_state`) which specifies whether this `Link` is active.
  role: an `enum` (`link_role`) labeling this `Link`'s role in the artificial neural network.
  inNode: the `Node*` from which this `Link`'s input signal originates.
  outNode: the `Node*` to which this `Link`'s ouput signal is relayed.
  weight: a `double` which determines the weight affecting this `Link`'s signal.

  Constructors:
  ------------
  complete: creates a `Link` instance by specifying all of its data.
  copy: makes a shallow copy of the input `Link`.

  Methods:
  -------
  engage: prompts this `Link` to relay a signal to and engage its target `Node`.
  graph: produces this `Link`'s associated `Graph` `Edge`.
*/

/*
  Contributors: Fernando Zago.
*/

#pragma once

#include <tuple>
#include "../neatnik/neatnik.h"

class Link
{
public:

    // Data:

    // A unique label specifying specifying this `Link`'s relative position within the artificial neural network.
    unsigned long int key;

    // A unique label specifying this `Link`'s identity within a `Genus`.
    unsigned int tag;

    // Control flag which specifies whether this `Link` is ENABLED or DISABLED.
    element_state state;

    // Establishes whether this instance behaves as a FORWARD, BIASING, RECURRENT or LOOPED `Link`.
    link_role role;

    // The source and target `Node`s connected by this `Link`.
    Node* inNode = nullptr;
    Node* outNode = nullptr;

    // The weight by which the signal originated in the source `Node` is multiplied by before being transmitted to the target `Node`.
    double weight;


    // Constructors:

    // Complete constructor for which all data specifying the `Link` is provided.
    Link(unsigned long int key_, unsigned int tag_, element_state state_, link_role role_, Node* inNode_, Node* outNode_, double weight_);

    // Copy constructor responsible for making a shallow copy of the input `Link`.
    Link(Link* thatLink_);


    // Methods:

    // Prompts this `Link` to relay a signal to and engage its target `Node`.
    void engage();

    // Produces this `Link`'s associated `Graph` `Edge`.
    Edge graph();
};
