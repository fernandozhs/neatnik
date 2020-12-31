#include "../organism/organism.h"

// Constructors:

// Initialization constructor responsible for building an `Organism` characterized by a minimal `Graph`.
Organism::Organism(Species* thatSpecies_, Graph thatGraph_)
{
    // Assigns this `Organism` to its taxon.
    species = thatSpecies_;

    // Assigns this `Organism` to the default group within its taxon.
    group = CONTESTANT;

    // Initializes this `Organism`'s `Phenotype`.
    phenotype = new Phenotype(this);

    // Initializes this `Organism`'s `Genotype`.
    genotype = new Genotype(this, thatGraph_);

    // Initializes this `Organism`'s age.
    age = 0;

    // Initializes this `Organism`'s score.
    score = 0.;
}

// Copy constructor responsible for making a deep copy of the input `Organism`.
Organism::Organism(Organism* thatOrganism_)
{
    // Assigns this `Organism` to its appropriate taxon.
    species = thatOrganism_->species;

    // Copies the input `Organism`'s taxonic group.
    group = thatOrganism_->group;

    // Copies the input `Organism`'s `Genotype`.
    genotype = new Genotype(this, thatOrganism_->genotype);

    // Initializes this `Organism`'s `Phenotype`.
    phenotype = new Phenotype(this);

    // Copies the input `Organism`'s age.
    age = thatOrganism_->age;

    // Copies the input `Organism`'s score.
    score = thatOrganism_->score;
}

// Reconstructs an `Organism` from an input `Graph`.
Organism::Organism(Graph thatGraph_)
{
    // Does not assigns this `Organism` to any taxon.
    species = nullptr;

    // Reconstructs the `Organism`'s `Genotype`.
    genotype = new Genotype(thatGraph_);

    // Initializes this `Organism`'s `Phenotype`.
    phenotype = new Phenotype(this);
}


// Destructor:

// Recursive destructor.
Organism::~Organism()
{
    // Deletes this `Organism`'s `Genotype`.
    delete genotype;

    // Deletes this `Organism`'s `Phenotype`.
    delete phenotype;
}


// Methods:

// Produces a new `Organism` through mutation.
Organism* Organism::mutate()
{
    // Initializes the new `Organism`.
    Organism* newOrganism_ = new Organism(this);

    // Mutates the new `Organism`.
    newOrganism_->genotype->mutate();

    // Sets the new `Organism`'s group.
    newOrganism_->group = CONTESTANT;

    // Sets the new `Organism`'s age.
    newOrganism_->age = 0;

    // Returns the new `Organism`.
    return newOrganism_;
}

// Produces a new `Organism` through assimilation.
Organism* Organism::assimilate(Organism* thatOrganism_)
{
    // Initializes the new `Organism`.
    Organism* newOrganism_ = new Organism(this);

    // Prompts the new `Organism` to assimilate the input `Organism`'s `Genotype`.
    newOrganism_->genotype->assimilate(thatOrganism_->genotype);

    // Sets the new `Organism`'s group.
    newOrganism_->group = CONTESTANT;

    // Sets the new `Organism`'s age.
    newOrganism_->age = 0;

    // Returns the new `Organism`.
    return newOrganism_;
}

// Prompts this `Organism` to react to the input stimuli.
std::vector<std::vector<double>> Organism::react(std::vector<std::vector<double>> stimuli_)
{
    // Initializes the output reactions.
    std::vector<std::vector<double>> reactions_;

    // Assembles this `Organism`'s `Phenotype`.
    phenotype->assemble();

    // Produces this `Organism`'s reaction to each input stimulus.
    for (const auto& stimulus_ : stimuli_)
    {
        // Activates this `Organism`'s `Phenotype`.
        phenotype->activate(stimulus_);

        // Stores the reaction to the current stimulus.
        reactions_.push_back(phenotype->output);

        // Deactivates this `Organism`'s `Phenotype`.
        phenotype->deactivate();
    }

    // Returns this `Organism`'s reactions.
    return reactions_;
}

// Produces the `Graph` associated with this `Organism`'s `Genotype`.
Graph Organism::graph() const
{
    // Returns the `Graph` associated with this `Organism`'s `Genotype`.
    return genotype->graph();
}
