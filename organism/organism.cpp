#include "organism.h"

// Constructor:

// Initialization constructor.
// TODO: Make the `Genotype` initialization more flexible.
Organism::Organism(Population* thatPopulation_, Archetype thatArchetype_)
{
    // Assigns this `Organism` to the pertinent `Population`.
    population = thatPopulation_;

    // Initializes this `Organism`'s `Phenotype`.
    phenotype = new Phenotype(this);

    // Initializes this `Organism`'s `Genotype`.
    genotype = new Genotype(this, thatArchetype_);
}

// Copy constructor responsible for making a deep copy of the input `Organism`.
Organism::Organism(Organism* thatOrganism_)
{
    // Assigns this `Organism` to the pertinent `Population`.
    population = thatOrganism_->population;

    // Initializes this `Organism`'s `Phenotype`.
    phenotype = new Phenotype(this);

    // Copies the input `Organism`'s `Genotype`.
    genotype = new Genotype(this, thatOrganism_->genotype);
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

// Mutates this `Organism`.
void Organism::mutate()
{
    // Mutates this `Organism`'s `Genotype`.
    this->genotype->mutate();

    return;
}

// Assimilates another `Organism` through a crossover operation.
void Organism::crossover(Organism* thatOrganism_)
{
    // Incorporates the input `Organism`'s `Genotype` into this `Organism`.
    this->genotype->crossover(thatOrganism_->genotype);

    return;
}

// Ranks this `Organism`'s performance with respect to a given metric.
void Organism::rank()
{
    // Measures this `Organism`'s performance and assigns it a score.
    // rank(this);

    return;
}


// Operators:

// Overloaded '<' operation for comparing two `Organism`s' scores or `Genotype` lengths.
bool Organism::operator <(const Organism& thatOrganism_) const
{
    // Checks whether the two `Organism`s possess the same score.
    if (this->score == thatOrganism_.score)
    {
        // Compares the `Organism`s according to the size of their `Genotype`s.
        return this->genotype->size() > thatOrganism_.genotype->size();
    }
    else
    {
        // Compares the `Organism`s according to their scores.
        return this->score < thatOrganism_.score;
    }
}
