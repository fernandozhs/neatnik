#include "link.h"

// Constructors:

// Complete constructor for which all data specifying the `Link` is provided.
Link::Link(long int key_, unsigned int tag_, element_state state_, link_role role_, Node* inNode_, Node* outNode_, double weight_)
{
    // Assings this `Link` a reference key.
    key = key_;

    // Assigns this `Link` an identification tag.
    tag = tag_;

    // Specifies whether this `Link` should be enabled at initialization.
    state = state_;

    // Establishes this `Link`'s role in the artifical neural network.
    role = role_;

    // Initializes the source and target `Node`s connected by this `Link`.
    inNode = inNode_;
    outNode = outNode_;

    // Assigns a weight to the connection.
    weight = weight_;
}

// Copy constructor responsible for making a shallow copy of the input `Link`.
Link::Link(Link* thatLink_)
{
    // Copies that `Link`'s reference key.
    key = thatLink_->key;

    // Copies that `Link`'s identification tag.
    tag = thatLink_->tag;

    // Copies that `Link`'s state which specifies whether it is currently enabled.
    state = thatLink_->state;

    // Copies that `Link`'s role in the artificial neural network.
    role = thatLink_->role;

    // Copies the source and target `Node`s connected by that `Link`.
    inNode = thatLink_->inNode;
    outNode = thatLink_->outNode;

    // Copies that `Link`'s weight.
    weight = thatLink_->weight;
}


// Methods:

// Prompts this `Link` to relay a signal to and engage its target `Node`.
void Link::engage()
{
    // Retrieves the input signal to be processed by this `Link`.
    double signal_ = inNode->output;

    // Weights the input signal and relays it to this `Link`'s target `Node`.
    outNode->inputs.push_back(weight*signal_);

    // Prompts this `Link`'s target `Node` to produce and broadcast a new output.
    outNode->engage();

    return;
}
