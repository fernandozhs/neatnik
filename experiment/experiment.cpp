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

// Sets up this `Experiment`.
void Experiment::build()
{
    // Initializes this `Experiment`'s starting minimal `Graph`s.
    std::vector<Graph> thoseGraphs_ (Parameters::population_size, Graph(vertexes, edges));

    // Populates this `Experiment`'s `Genus` with `Organism`s initialized from such minimal `Graph`s.
    genus = new Genus(this, thoseGraphs_);

    return;
}

// Runs this `Experiment`.
void Experiment::run()
{
    // Runs this `Experiment`.
    for (int cycles_ = Parameters::generational_cycles; cycles_ >= 0; --cycles_)
    {
        // Displays any of this `Experiment`'s current data.
        this->display();

        // Drives the evolution of this `Experiment`'s `Genus`.
        this->drive(Parameters::evolution_driver);
    }

    return;
}

// Displays any of this `Experiment`'s current data.
void Experiment::display()
{
    // Does not display any information by default.
    return;
}

// Drives the evolution of this `Experiment`'s `Genus`.
void Experiment::drive(driver_metric metric_)
{
    // Ranks each `Species` in this `Experiment`'s `Genus` according to the input driver metric.
    for (const auto& theSpecies_ : genus->retrieve({DOMINANT, CONTESTANT}))
    {
        // Resets the current `Species`' rank.
        switch (metric_)
        {
            case NOVELTY:
                // NOVELTY is assessed for both CONTESTANT and DOMINANT `Organism`s, requiring `Species`' ranks to be completely cleared.
                theSpecies_->rank = 0.;
                break;

            case FITNESS:
                // FITNESS is only assessed for CONTESTANT `Organism`s, requiring `Species`' ranks to be offset by their DOMINANT `Organism`'s FITNESS score.
                theSpecies_->rank = 0. + theSpecies_->front(DOMINANT)->scores[FITNESS];
                break;

            default:
                // No other driver metric has been implemented.
                break;
        }

        // Scores the appropriate `Organism`s in the current `Species`.
        switch (metric_)
        {
            case NOVELTY:
                // Assesses both the NOVELTY and FITNESS scores of all `Organism` in the current `Species`. Each NOVELTY score is accumulated into the current `Species`' rank.
                for (const auto& theOrganism_ : theSpecies_->retrieve({DOMINANT, CONTESTANT}))
                {
                    this->assess(theOrganism_, {NOVELTY, FITNESS});
                    theSpecies_->rank += theOrganism_->scores[NOVELTY];
                }
                break;

            case FITNESS:
                // Assesses the FITNESS score of each CONTESTANT `Organism` in the current `Species`. Each FITNESS score is accumulated into the current `Species`' rank.
                for (const auto& theOrganism_ : theSpecies_->retrieve({CONTESTANT}))
                {
                    this->assess(theOrganism_, {FITNESS});
                    theSpecies_->rank += theOrganism_->scores[FITNESS];
                }
                break;

            default:
                // No other driver metric has been implemented.
                break;
        }

        // Ranks the current `Species` according to its size.
        theSpecies_->rank /= theSpecies_->size({DOMINANT, CONTESTANT});
    }

    // Evolves this `Experiment`'s `Genus`.
    genus->spawn();
    genus->select();
    genus->speciate();

    return;
}

// Scores and curates the input `Organism` with respect to the given performance metric(s).
void Experiment::assess(Organism* thatOrganism_, const std::vector<int> metrics_)
{
    // Scores and curates the input `Organism`.
    for (const auto& metric_ : metrics_)
    {
        // Scores the input `Organism`.
        switch (metric_)
        {
            case NOVELTY:
                // Assigns the input `Organism` a behavior and NOVELTY score.
                thatOrganism_->behavior = this->behavior(thatOrganism_);
                thatOrganism_->scores[NOVELTY] = this->novelty(thatOrganism_);
                break;

            case FITNESS:
                // Assigns the input `Organism` a FITNESS score.
                thatOrganism_->scores[FITNESS] = this->fitness(thatOrganism_);
                break;

            default:
                // No other driver metric has been implemented.
                break;
        }

        // Curates the input `Organism`.
        switch (metric_)
        {
            case NOVELTY:
                // Stores the behaviors of threshold-clearing `Organism`s and updates this `Experiment`'s NOVELTY threshold.
                if (thatOrganism_->scores[NOVELTY] >= Parameters::novelty_threshold)
                {
                    behaviors.push_back(thatOrganism_->behavior);
                    Parameters::novelty_threshold *= Parameters::novelty_threshold_modifiers[0];
                }
                else
                {
                    Parameters::novelty_threshold *= Parameters::novelty_threshold_modifiers[1];
                }
                break;

            case FITNESS:
                // Stores the `Graph`s of threshold-clearing `Organism`s and updates this `Experiment`'s FITNESS threshold.
                if (thatOrganism_->scores[FITNESS] > Parameters::fitness_threshold)
                {
                    outcome.push_back(thatOrganism_->graph());
                    Parameters::fitness_threshold = thatOrganism_->scores[FITNESS];
                }
                break;

            default:
                // No other driver metric has been implemented.
                break;
        }
    }

    return;
}

// Evaluates the input `Organism`'s NOVELTY score.
double Experiment::novelty(Organism* thatOrganism_)
{
    // Checks whether this `Experiment` has stored any behaviors.
    if (behaviors.size() == 0)
    {
        // Returns the threshold NOVELTY score.
        return Parameters::novelty_threshold;
    }
    else
    {
        // Returns the input `Organism`'s NOVELTY score.
        return Sparseness(Parameters::novelty_neighbors, behaviors, thatOrganism_->behavior);
    }
}
