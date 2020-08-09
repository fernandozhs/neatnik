#include "node.h"

// Constructors:

// Complete constructor for which all non-dynamic data specifying the `Node` is provided.
Node::Node(Innovation* innovation_, element_state state_, node_role role_, activation function_, double x_, double y_)
{
    // Tags this `Node` as a way of tracking its first appearance in the `Population`.
    innovation = innovation_;

    // Specifies whether this `Node` should be enabled at initialization.
    state = state_;

    // Establishes this `Node`'s role within the artificial neural network.
    role = role_;

    // Initializes this `Node`'s activation function.
    function = function_;

    // Initializes this `Node`'s coordinates.
    x = x_;
    y = y_;
}

// Split constructor resposible for initializing a new `Node` instance placed half-way between two other `Node`s.
Node::Node(Innovation* innovation_, element_state state_, node_role role_, Node* inNode_, Node* outNode_, activation function_)
{
    // Tags this `Node` as a way of tracking its first appearance in the `Population`.
    innovation = innovation_;

    // Specifies whether this `Node` should be enabled at initialization.
    state = state_;

    // Establishes this `Node`'s role within the artificial neural network.
    role = role_;

    // Initializes this `Node`'s activation function.
    function = function_;

    // Initializes this `Node`'s coordinates.
    x = (inNode_->x + outNode_->x)/2;
    y = (inNode_->y + outNode_->y)/2;
}

// Copy constructor responsible for making a shallow copy of the input `Node`.
Node::Node(Node* thatNode_)
{
    // Copies that `Node`'s identification tag as a way of tracking its first appearance in the `Population`.
    innovation = thatNode_->innovation;

    // Copies that `Node`'s state which specifies whether it is currently enabled.
    state = thatNode_->state;

    // Copies that `Node`'s role in the artificial neural network.
    role = thatNode_->role;

    // Copies that `Node`'s activation function.
    function = thatNode_->function;

    // Copies that `Node`'s coordinates.
    x = thatNode_->x;
    y = thatNode_->y;
}


// Methods:

// Prompts this `Node` to produce and broadcast an output signal.
void Node::engage()
{
    // Checks whether all input signals arriving at this `Node` have been accumulated.
    if (inputs.size() != inLinks.size())
    {
        // Failed to engage this `Node`.
        return;
    }
    else
    {
        // Produces this `Node`'s output signal.
        output = function(inputs);

        // Broadcasts this `Node`'s newly produced output signal.
        for (const auto& theLink_ : outLinks)
        {
            // Prompts the current `Link` to relay a signal and engage its target `Node`.
            theLink_->engage();
        }

        // Successfully engaged this `Node`.
        return;
    }
}

// Primes this `Node` for a subsequent engagement.
void Node::disengage()
{
    // Discards this `Node`'s inputs.
    inputs.clear();

    return;
}

// Makes this `Node` assimilate another `Node`'s activation function.
void Node::assimilate(Node* thatNode_)
{
    // Incorporates the input `Node`'s activation function.
    function = thatNode_->function;

    return;
}


// Operators:

// Overloaded '<' operation for comparing two `Node`s' innovation tags.
bool Node::operator<(const Node& thatNode_) const
{
    return this->innovation->tag < thatNode_.innovation->tag;
}

// Overloaded '==' operation for checking whether two `Node`s possess the same identification tags.
bool Node::operator ==(const Node& thatNode_) const
{
    return this->innovation->tag == thatNode_.innovation->tag;
}
