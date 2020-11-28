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

    // Accumulates the performance score of each `Organism`.
    for (const auto& theOrganism_ : thatSpecies_->organisms->retrieve({DOMINANT, CONTESTANT}))
    {
        // Increments the curret `Organism`'s age.
        theOrganism_->age++;

        // Accumulates the curret `Organism`'s score.
        switch (theOrganism_->batch)
        {
            // Accumulates the DOMINANT `Organism`'s performance score.
            case DOMINANT:
                thatSpecies_->score += theOrganism_->score;
                break;

            // Evaluates and accumulates the CONTESTANT `Organism`'s score.
            case CONTESTANT:
                theOrganism_->score = this->evaluate(theOrganism_);
                thatSpecies_->score += theOrganism_->score;
                break;
        }
    }

    // Scores the input `Species` with the average of its `Organism`s' scores.
    thatSpecies_->score /= thatSpecies_->organisms->size({DOMINANT, CONTESTANT});

    return;
}

// Evaluates the performance of the input `Organism`.
double Experiment::evaluate(Organism* thatOrganism_)
{
    // Initializes the return variable.
    double score_ = 0.;

    // Assembles the input `Organism`'s `Phenotype`.
    thatOrganism_->phenotype->assemble();

    /*
      Tests the performance of the input `Organism`'s `Phenotype`.
    */

    // Returns the `Organism`'s score based on its `Phenotype` performance.
    return score_;
}
