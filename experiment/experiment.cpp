#include "experiment.h"

// Constructor:

// Constructor responsible for initializing this `Experiment`.
Experiment::Experiment()
{
    // Initializes this this `Experiment`'s `Parameters`.
    parameters = new Parameters();
}


// Destructor:

// Destructor responsible for recursively deleting this `Experiment` and its associated `Parameters` and `Genus`.
Experiment::~Experiment()
{
    // Deletes this `Experiment`'s `Parameters`.
    delete parameters;

    // Deletes this `Experiment`'s `Genus`.
    delete genus;
}


// Methods:

// Populates this `Experiment`'s `Genus`.
void Experiment::populate()
{
    // Initializes this `Experiment`'s starting minimal `Graph`s.
    std::vector<Graph> thoseGraphs_ (parameters->population_size, Graph(vertexes, edges));

    // Populates this `Experiment`'s `Genus` with `Organism`s initialized from such minimal `Graph`s.
    genus = new Genus(this, thoseGraphs_);

    return;
}

// Runs this `Experiment`.
void Experiment::run(bool verbose_)
{
    // Runs this `Experiment`.
    for (int cycles_ = parameters->generational_cycles; cycles_; --cycles_)
    {
        // Prints this `Experiment`'s progress.
        if (verbose_)
        {
            std::cout << "Progress: ";
            std::cout << std::right << std::setw(4) << std::setprecision(1) << std::fixed;
            std::cout << 100 - 100*(double)cycles_/parameters->generational_cycles;
            std::cout << "% ";
            std::cout << "(" << parameters->generational_cycles - cycles_ << "/" << parameters->generational_cycles << ") - ";
            std::cout << "Highest Score: " << genus->front(DOMINANT)->front(DOMINANT)->score;
            std::cout << "\r" << std::flush;
        }

        // Evaluates the `Genus`' performance.
        this->evaluate();

        // Finds the best performing `Organism`s and purges any stagnated `Species`.
        genus->select();

        // Spawns a new generation of `Organism`s.
        genus->spawn();

        // Assigns each spawned `Organism` to a new or existing `Species`.
        genus->speciate();
    }

    // Warns that this `Experiment` has ended.
    if (verbose_)
    {
        std::cout << std::endl;
    }

    return;
}

// Evaluates the performance of this `Experiment`'s `Genus`.
void Experiment::evaluate()
{
    // Evaluates the performance of each `Species`.
    for (const auto& theSpecies_ : genus->retrieve({DOMINANT, CONTESTANT}))
    {
        // Resets the current `Species`' rank.
        theSpecies_->rank = theSpecies_->front(DOMINANT)->score;

        // Evaluates and accumulates each CONTESTANT `Organism`'s score.
        for (const auto& theOrganism_ : theSpecies_->retrieve({CONTESTANT}))
        {
            theOrganism_->score = this->performance(theOrganism_);
            theSpecies_->rank += theOrganism_->score;
        }

        // Ranks the input `Species`.
        theSpecies_->rank /= theSpecies_->size({DOMINANT, CONTESTANT});
    }

    return;
}
