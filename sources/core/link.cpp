#include "link.hpp"


// Constructors:

Link::Link(unsigned long int key_, unsigned int tag_, element_state state_, link_role role_, Node* source_, Node* target_, double weight_)
{
    key = key_;

    tag = tag_;

    state = state_;

    role = role_;

    source = source_;
    target = target_;

    weight = weight_;
}

Link::Link(Link* link_)
{
    key = link_->key;

    tag = link_->tag;

    state = link_->state;

    role = link_->role;

    source = link_->source;
    target = link_->target;

    weight = link_->weight;
}


// Methods:

void Link::engage()
{
    double signal_ = source->output;

    target->inputs.push_back(weight*signal_);

    target->engage();

    return;
}

Edge Link::graph()
{
    Edge edge_ (key, tag, state, role, source->key, target->key, weight);

    return edge_;
}
