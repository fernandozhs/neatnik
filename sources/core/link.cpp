#include "link.hpp"


// Constructors:

Link::Link(Key key_, std::uint32_t tag_, element_state state_, link_role role_, Node* source_, Node* target_, double weight_)
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

LinkData Link::data()
{
    LinkData data_ (tag, state, role, weight, std::get<2>(key), std::get<3>(key));

    return data_;
}
