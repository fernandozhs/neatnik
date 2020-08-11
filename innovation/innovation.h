/*
  An `Innovation` is a data structure which labels a new `Link` or `Node` added to a `Genotype`.
 
  Data:
  ----
  type: an enumerated type (`element_type`) labeling the nature of this `Innovation`.
  in_tag: an `integer` which uniquely specifies one of the two `Node`s between which the innovation took place.
  out_tag: an `integer` which uniquely specifies one of the two `Node`s between which the innovation took place.
  tag: an `integer` which uniquely labels this `Innovation`.

  Constructor:
  -----------
  complete: initializes an `Innovation` by specifying all of its data.
*/

/*
  Contributors: Fernando Zago.
*/

#pragma once

#include "../neatnik/neatnik.h"

struct Innovation
{
public:

    // Data:

    // Records whether this `Innovation` corresponds to a new `Link` or `Node`.
    element_type type;

    // The identification tags labeling to the two `Node`s between which the innovation took place, i.e., either the two `Node`s between which a new `Link` was formed, or the two connected `Node`s between which a new `Node` was inserted.
    unsigned int in_tag;
    unsigned int out_tag;

    // This `Innovation`'s unique label.
    unsigned int tag;


    // Constructor:

    // Complete constructor.
    Innovation(element_type type_, unsigned int in_tag_, unsigned int out_tag_, unsigned int tag_);
};
