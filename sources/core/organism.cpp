#include "organism.hpp"


// Constructors:

Organism::Organism(Species* species_, Graph graph_)
{
    species = species_;

    group = CONTESTANT;

    phenotype = new Phenotype(this);

    genotype = new Genotype(this, graph_);

    age = 0;

    score = 0.;
}

Organism::Organism(Organism* organism_)
{
    species = organism_->species;

    group = organism_->group;

    genotype = new Genotype(this, organism_->genotype);

    phenotype = new Phenotype(this);

    age = organism_->age;

    score = organism_->score;
}

Organism::Organism(Graph graph_)
{
    species = nullptr;

    genotype = new Genotype(graph_);

    phenotype = new Phenotype(this);
}


// Destructor:

Organism::~Organism()
{
    delete genotype;

    delete phenotype;
}


// Methods:

Organism* Organism::mutate()
{
    Organism* offspring_ = new Organism(this);

    offspring_->genotype->mutate();

    offspring_->group = CONTESTANT;

    offspring_->age = 0;

    return offspring_;
}

Organism* Organism::assimilate(Organism* organism_)
{
    // Initializes the new `Organism`.
    Organism* offspring_ = new Organism(this);

    offspring_->genotype->assimilate(organism_->genotype);

    offspring_->group = CONTESTANT;

    offspring_->age = 0;

    return offspring_;
}

std::vector<std::vector<std::vector<double>>> Organism::react()
{
    std::vector<std::vector<std::vector<double>>> reactions_;
    reactions_.reserve(species->genus->experiment->stimuli.size());

    std::vector<std::vector<double>> outputs_;

    phenotype->assemble();

    for (const auto& inputs_ : species->genus->experiment->stimuli)
    {
        outputs_.clear();

        for (const auto& input_ : inputs_)
        {
            phenotype->activate(input_);
            outputs_.push_back(phenotype->output);
            phenotype->deactivate();
        }

        phenotype->discontinue();

        reactions_.push_back(outputs_);
    }

    return reactions_;
}

std::vector<std::vector<std::vector<double>>> Organism::react(std::vector<std::vector<std::vector<double>>> stimuli_)
{
    std::vector<std::vector<std::vector<double>>> reactions_;
    reactions_.reserve(stimuli_.size());

    std::vector<std::vector<double>> outputs_;

    phenotype->assemble();

    for (const auto& inputs_ : stimuli_)
    {
        outputs_.clear();

        for (const auto& input_ : inputs_)
        {
            phenotype->activate(input_);
            outputs_.push_back(phenotype->output);
            phenotype->deactivate();
        }

        phenotype->discontinue();

        reactions_.push_back(outputs_);
    }

    return reactions_;
}

Graph Organism::graph() const
{
    return genotype->graph();
}
