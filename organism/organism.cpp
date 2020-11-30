#include "organism.h"

// Constructor:

// Initialization constructor.
// TODO: Make the `Genotype` initialization more flexible.
Organism::Organism(Species* thatSpecies_, Archetype thatArchetype_)
{
    // Assigns this `Organism` to its taxon.
    species = thatSpecies_;

    // Assigns this `Organism` to the default group within its taxon.
    group = CONTESTANT;

    // Initializes this `Organism`'s `Phenotype`.
    phenotype = new Phenotype(this);

    // Initializes this `Organism`'s `Genotype`.
    genotype = new Genotype(this, thatArchetype_);

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
