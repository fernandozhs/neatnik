#include "node.hpp"


// Constructors:

Node::Node(unsigned long int key_, unsigned int tag_, element_state state_, node_role role_, node_activation activation_, double x_, double y_)
{
    key = key_;

    tag = tag_;

    state = state_;

    role = role_;

    activation = activation_;

    x = x_;
    y = y_;
}

Node::Node(unsigned long int key_, unsigned int tag_, element_state state_, node_role role_, Node* source_, Node* target_, node_activation activation_)
{
    key = key_;

    tag = tag_;

    state = state_;

    role = role_;

    activation = activation_;

    x = (source_->x + target_->x)/2;
    y = (source_->y + target_->y)/2;
}

Node::Node(Node* node_)
{
    key = node_->key;

    tag = node_->tag;

    state = node_->state;

    role = node_->role;

    activation = node_->activation;

    x = node_->x;
    y = node_->y;
}


// Methods:

double Node::activate()
{
    switch (activation)
    {
        case HEAVISIDE:
            return Heaviside(inputs);
            break;

        case RELU:
            return ReLU(inputs);
            break;

        case LOGISTIC:
            return Logistic(inputs);
            break;

        case IDENTITY:
            return Identity(inputs);
            break;

        case UNITY:
            return Unity(inputs);
            break;
    }
}

void Node::engage()
{
    if (inputs.size() != incoming.size())
    {
        return;
    }
    else
    {
        output = this->activate();

        for (const auto& link_ : outgoing)
        {
            link_->engage();
        }

        return;
    }
}

void Node::disengage()
{
    inputs.clear();

    return;
}

void Node::clear()
{
    output = 0;

    return;
}

Vertex Node::graph()
{
    Vertex vertex_ (key, tag, state, role, activation, x, y);

    return vertex_;
}

