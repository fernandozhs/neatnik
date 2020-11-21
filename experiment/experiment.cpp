#include "experiment.h"

// Methods:

// Evaluates the performance of the input `Genus`.
void Experiment::evaluate(Genus* thatGenus_)
{
    // Evaluates the performance score of each `Species`.
    for (const auto& theSpecies_ : thatGenus_->species->retrieve({DOMINANT, CONTESTANT}))
    {
        this->evaluate(theSpecies_);
    }

    return;
}

// Evaluates the performance of the input `Species`.
void Experiment::evaluate(Species* thatSpecies_)
{
    // Resets the input `Species`' score.
    thatSpecies_->score = 0.;

    // Accumulates the performance score of each DOMINANT `Organism`s.
    for (const auto& theOrganism_ : thatSpecies_->organisms->retrieve({DOMINANT}))
    {
        thatSpecies_->score += theOrganism_->score;
    }

    // Evaluates and accumulates the performance score of each CONTESTANT `Organism`.
    for (const auto& theOrganism_ : thatSpecies_->organisms->retrieve({CONTESTANT}))
    {
        theOrganism_->score = this->evaluate(theOrganism_);
        thatSpecies_->score += theOrganism_->score;
    }

    // Scores the `Species` with average of its `Organism`s' scores.
    thatSpecies_->score /= thatSpecies_->organisms->size({DOMINANT, CONTESTANT});

    return;
}

// Evaluates the performance of the input `Organism`.
double Experiment::evaluate(Organism* thatOrganism_)
{
    // Initializes the return variable.
    double score_ = 0.;

    // Increments the input `Organism`'s age and assembles its `Phenotype`.
    thatOrganism_->age++;
    thatOrganism_->phenotype->assemble();

    /*
      Tests the performance of the input `Organism`'s `Phenotype`.
    */

    // Returns the `Organism`'s score based on its `Phenotype` performance.
    return score_;
}
