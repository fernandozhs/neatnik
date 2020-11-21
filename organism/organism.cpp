#include "organism.h"

// Constructor:

// Initialization constructor.
// TODO: Make the `Genotype` initialization more flexible.
Organism::Organism(Species* thatSpecies_, Archetype thatArchetype_)
{
    // Assigns this `Organism` to the pertinent `Species`.
    species = thatSpecies_;

    // Initializes this `Organism`'s `Phenotype`.
    phenotype = new Phenotype(this);

    // Initializes this `Organism`'s `Genotype`.
    genotype = new Genotype(this, thatArchetype_);

    // Assigns this `Organism` to the default batch.
    batch = CONTESTANT;

    // Initializes this `Organism`'s age.
    age = 0;

    // Initializes this `Organism`'s score.
    score = 0.;
}

// Copy constructor responsible for making a deep copy of the input `Organism`.
Organism::Organism(Organism* thatOrganism_)
{
    // Assigns this `Organism` to the pertinent `Species`.
    species = thatOrganism_->species;

    // Initializes this `Organism`'s `Phenotype`.
    phenotype = new Phenotype(this);

    // Copies the input `Organism`'s `Genotype`.
    genotype = new Genotype(this, thatOrganism_->genotype);

    // Copies the input `Organism`'s batch.
    batch = thatOrganism_->batch;

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

    // Sets the new `Organism`'s age.
    newOrganism_->age = 0;

    // Returns the new `Organism`.
    return newOrganism_;
}
