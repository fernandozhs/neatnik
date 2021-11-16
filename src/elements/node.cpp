#include "../elements/node.hpp"

// Constructors:

// Complete constructor for which all non-dynamic data specifying the `Node` is provided.
Node::Node(unsigned long int key_, unsigned int tag_, element_state state_, node_role role_, node_activation activation_, double x_, double y_)
{
    // Assings this `Node` a reference key.
    key = key_;

    // Assigns this `Node` an identification tag.
    tag = tag_;

    // Specifies whether this `Node` should be enabled at initialization.
    state = state_;

    // Establishes this `Node`'s role within the artificial neural network.
    role = role_;

    // Initializes this `Node`'s activation.
    activation = activation_;

    // Initializes this `Node`'s coordinates.
    x = x_;
    y = y_;
}

// Split constructor resposible for initializing a new `Node` located half-way between two other `Node`s.
Node::Node(unsigned long int key_, unsigned int tag_, element_state state_, node_role role_, Node* inNode_, Node* outNode_, node_activation activation_)
{
    // Assings this `Node` a reference key.
    key = key_;

    // Assigns this `Node` an identificatin tag.
    tag = tag_;

    // Specifies whether this `Node` should be enabled at initialization.
    state = state_;

    // Establishes this `Node`'s role within the artificial neural network.
    role = role_;

    // Initializes this `Node`'s activation.
    activation = activation_;

    // Initializes this `Node`'s coordinates.
    x = (inNode_->x + outNode_->x)/2;
    y = (inNode_->y + outNode_->y)/2;
}

// Copy constructor responsible for making a shallow copy of the input `Node`.
Node::Node(Node* thatNode_)
{
    // Copies that `Node`'s reference key.
    key = thatNode_->key;

    // Copies that `Node`'s identification tag.
    tag = thatNode_->tag;

    // Copies that `Node`'s state which specifies whether it is currently enabled.
    state = thatNode_->state;

    // Copies that `Node`'s role in the artificial neural network.
    role = thatNode_->role;

    // Copies that `Node`'s activation.
    activation = thatNode_->activation;

    // Copies that `Node`'s coordinates.
    x = thatNode_->x;
    y = thatNode_->y;
}


// Methods:

// Produces this `Node`'s output signal.
double Node::activate()
{
    // Selects the function matching this `Node`'s activation.
    switch (activation)
    {
        case HEAVISIDE:
            // Heaviside activation function.
            return Heaviside(inputs);
            break;

        case RELU:
            // Rectified Linear Unit activation function.
            return ReLU(inputs);
            break;

        case LOGISTIC:
            // Logistic activation function.
            return Logistic(inputs);
            break;

        case IDENTITY:
            // Identity function.
            return Identity(inputs);
            break;

        case UNITY:
            // Unity function.
            return Unity(inputs);
            break;
    }
}

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
        output = this->activate();

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

// Produces this `Node`'s associated `Graph` `Vertex`.
Vertex Node::graph()
{
    // Builds this `Node`'s associated `Vertex`.
    Vertex theVertex_ (key, tag, state, role, activation, x, y);

    // Returns the `Vertex`.
    return theVertex_;
}

