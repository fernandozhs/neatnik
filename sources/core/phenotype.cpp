#include "phenotype.hpp"


// Constructor:

Phenotype::Phenotype(Organism* organism_)
{
    organism = organism_;
}


// Methods:

void Phenotype::assemble()
{
    this->disassemble();

    for (const auto& link_ : organism->genotype->links->retrieve({RECURRENT, LOOPED}, {ENABLED}))
    {
        link_->target->incoming.push_back(link_);
    }

    for (const auto& link_ : organism->genotype->links->retrieve({FORWARD, BIASING}, {ENABLED}))
    {
        link_->target->incoming.push_back(link_);
        link_->source->outgoing.push_back(link_);
    }

    return;
}

void Phenotype::disassemble()
{
    this->deactivate();

    for (const auto& node_ : organism->genotype->nodes->retrieve({INPUT, BIAS}, {ENABLED}))
    {
        node_->outgoing.clear();
    }

    for (const auto& node_ : organism->genotype->nodes->retrieve({HIDDEN, OUTPUT}, {ENABLED}))
    {
        node_->incoming.clear();
        node_->outgoing.clear();
    }

    return;
}

void Phenotype::activate(std::vector<double> inputs_)
{
    for (const auto& link_ : organism->genotype->links->retrieve({RECURRENT, LOOPED}, {ENABLED}))
    {
        link_->engage();
    }

    for (const auto& node_ : organism->genotype->nodes->retrieve({INPUT, BIAS}, {ENABLED}))
    {
        switch (node_->role)
        {
            case INPUT:
                node_->inputs.push_back(inputs_.at(node_->tag));
                node_->engage();
                break;

            case BIAS:
                node_->inputs.push_back(1.);
                node_->engage();
                break;

            default:
                break;
        }
    }

    for (const auto& node_ : organism->genotype->nodes->sort({OUTPUT}, {ENABLED}))
    {
        output.push_back(node_->output);
    }

    return;
}

void Phenotype::deactivate()
{
    for (const auto& node_ : organism->genotype->nodes->retrieve({INPUT, BIAS, HIDDEN, OUTPUT}, {ENABLED}))
    {
        node_->disengage();
    }

    output.clear();

    return;
}

void Phenotype::discontinue()
{
    for (const auto& node_ : organism->genotype->nodes->retrieve({HIDDEN, OUTPUT}, {ENABLED}))
    {
        node_->clear();
    }

    return;
}
