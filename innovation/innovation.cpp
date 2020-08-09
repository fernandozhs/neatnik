#include "innovation.h"

// Constructors:

// Complete constructor.
Innovation::Innovation(element_type type_, int in_tag_, int out_tag_, int tag_)
{
    // Sets this `Innovation`'s type.
    type = type_;

    // Stores the identification tags of the two `Node`s between which the innovation took place.
    in_tag = in_tag_;
    out_tag = out_tag_;

    // Assigns this `Innovation`'s unique label.
    tag = tag_;
}
