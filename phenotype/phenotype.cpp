#include "../phenotype/phenotype.h"

// Constructor:

// Constructor responsible for initializing this `Phenotype` and assigns it to its associated `Organism`.
Phenotype::Phenotype(Organism* organism_)
{
    // Assigns this `Phenotype` to an `Organism`.
    organism = organism_;
}


// Methods:

// Assembles this `Phenotype`.
void Phenotype::assemble()
{
    // Disassembles this `Phenotype` prior to assemblage.
    this->disassemble();

    // Assembles all RECURRENT and LOOPED `Link`s.
    for (const auto& theLink_ : organism->genotype->links->retrieve({RECURRENT, LOOPED}, {ENABLED}))
    {
        theLink_->outNode->inLinks.push_back(theLink_);
    }

    // Assembles all FORWARD and BIASING `Link`s.
    for (const auto& theLink_ : organism->genotype->links->retrieve({FORWARD, BIASING}, {ENABLED}))
    {
        theLink_->outNode->inLinks.push_back(theLink_);
        theLink_->inNode->outLinks.push_back(theLink_);
    }

    return;
}

// Disassembles this `Phenotype`.
void Phenotype::disassemble()
{
    // Deactivates this `Phenotype` prior to disassemblage.
    this->deactivate();

    // Disassembles all `Link`s stemming from INPUT and BIAS `Node`s.
    for (const auto& theNode_ : organism->genotype->nodes->retrieve({INPUT, BIAS}, {ENABLED}))
    {
        theNode_->outLinks.clear();
    }

    // Disassembles all `Link`s stemming from and arriving at HIDDEN and OUTPUT `Node`s.
    for (const auto& theNode_ : organism->genotype->nodes->retrieve({HIDDEN, OUTPUT}, {ENABLED}))
    {
        theNode_->inLinks.clear();
        theNode_->outLinks.clear();
    }

    return;
}

// Propagates an input signal through this `Phenotype` and stores its output.
void Phenotype::activate(std::vector<double> inputs_)
{
    // Engages all RECURRENT and LOOPED `Link`s.
    for (const auto& theLink_ : organism->genotype->links->retrieve({RECURRENT, LOOPED}, {ENABLED}))
    {
        theLink_->engage();
    }

    // Engages all INPUT and BIAS `Node`s, recursively triggering all other `Node`s to be engaged as well.
    for (const auto& theNode_ : organism->genotype->nodes->retrieve({INPUT, BIAS}, {ENABLED}))
    {
        switch (theNode_->role)
        {
            case INPUT:
                // Passes the input signal to each INPUT `Node` and then engages them.
                theNode_->inputs.push_back(inputs_.at(theNode_->tag));
                theNode_->engage();
                break;

            case BIAS:
                // Passes a token input to the BIAS `Node` and then engages it.
                theNode_->inputs.push_back(1.);
                theNode_->engage();
                break;
        }
    }

    // Extracts this `Phenotype`'s output.
    for (const auto& theNode_ : organism->genotype->nodes->sort({OUTPUT}, {ENABLED}))
    {
        output.push_back(theNode_->output);
    }

    return;
}

// Restores this `Phenotype` to a clean slate.
void Phenotype::deactivate()
{
    // Disengages all ENABLED `Node`s.
    for (const auto& theNode_ : organism->genotype->nodes->retrieve({INPUT, BIAS, HIDDEN, OUTPUT}, {ENABLED}))
    {
        theNode_->disengage();
    }

    // Clears this `Phenotype`'s output.
    output.clear();

    return;
}
