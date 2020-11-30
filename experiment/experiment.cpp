#include "experiment.h"

// Constructor:

// Initializes this `Experiment`.
Experiment::Experiment(Genus* thatGenus_)
{
    // Specifies the `Genus` to be evolved by this `Experiment`.
    genus = thatGenus_;
}


// Methods:

// Prints this `Experiment`'s status.
void Experiment::status(int cycle_)
{
    //
}

// Evolves this `Experiment`'s `Genus`.
void Experiment::evolve(int cycles_, bool verbose_)
{
    // Prints the this `Experiment`'s initial status.
    if (verbose_) this->status(cycles_);

    // Evolves this `Experiment`'s `Genus` through a number of cycles.
    while (cycles_--)
    {
        // Prints this `Experiment`'s current status.
        if (verbose_) this->status(cycles_);

        // Evaluates the `Genus`' performance.
        this->evaluate();

        // Finds the best performing `Organism`s and purges any stagnated `Species`.
        genus->select();

        // Spawns a new generation of `Organism`s.
        genus->spawn();

        // Assigns each spawned `Organism` to a new or existing `Species`.
        genus->speciate()
    }

    // Prints the this `Experiment`'s final status.
    if (verbose_) this->status(cycles_);

    return;
}

// Evaluates the performance of this `Experiment`'s `Genus`.
void Experiment::evaluate()
{
    // Evaluates the performance score of each `Species`.
    for (const auto& theSpecies_ : genus->retrieve({DOMINANT, CONTESTANT}))
    {
        // Resets the current `Species`' rank.
        theSpecies_->rank = theSpecies_->front(DOMINANT)->score;

        // Evaluates and accumulates each CONTESTANT `Organism`'s score.
        for (const auto& theOrganism_ : theSpecies_->retrieve({CONTESTANT}))
        {
            theOrganism_->score = this->performance(theOrganism_->phenotype);
            theSpecies_->rank += theOrganism_->score;
        }

        // Ranks the input `Species`.
        theSpecies_->rank /= theSpecies_->size({DOMINANT, CONTESTANT});
    }

    return;
}

// Scores the performance of the input `Phenotype`.
double Experiment::performance(Phenotype* thatPhenotype_)
{
    // Initializes the return variable.
    double score_ = 0.;

    // Assembles the input `Organism`'s `Phenotype`.
    thatPhenotype->assemble();

    /*
      Tests the performance of the input `Organism`'s `Phenotype`.
    */

    // Returns the `Organism`'s score based on its `Phenotype` performance.
    return score_;
}
