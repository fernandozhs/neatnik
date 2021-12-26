#include "experiment.hpp"


std::vector<std::vector<std::vector<double>>> Experiment::stimuli;


// Constructor:

Experiment::Experiment()
{

}


// Destructor:

Experiment::~Experiment()
{
    delete genus;
}


// Methods:

void Experiment::build()
{
    std::vector<Graph> thoseGraphs_ (Parameters::population_size, Graph(vertexes, edges));

    genus = new Genus(this, thoseGraphs_);

    return;
}

void Experiment::run()
{
    for (int cycles_ = Parameters::generational_cycles; cycles_ >= 0; --cycles_)
    {
        this->display();

        this->drive(Parameters::evolution_driver);
    }

    return;
}

void Experiment::display()
{
    return;
}

void Experiment::drive(driver_metric metric_)
{
    for (const auto& theSpecies_ : genus->retrieve({DOMINANT, CONTESTANT}))
    {
        switch (metric_)
        {
            case NOVELTY:
                theSpecies_->rank = 0.;
                break;

            case FITNESS:
                theSpecies_->rank = 0. + theSpecies_->front(DOMINANT)->scores[FITNESS];
                break;

            default:
                break;
        }

        switch (metric_)
        {
            case NOVELTY:
                for (const auto& theOrganism_ : theSpecies_->retrieve({DOMINANT, CONTESTANT}))
                {
                    this->assess(theOrganism_, {NOVELTY, FITNESS});
                    theSpecies_->rank += theOrganism_->scores[NOVELTY];
                }
                break;

            case FITNESS:
                for (const auto& theOrganism_ : theSpecies_->retrieve({CONTESTANT}))
                {
                    this->assess(theOrganism_, {FITNESS});
                    theSpecies_->rank += theOrganism_->scores[FITNESS];
                }
                break;

            default:
                break;
        }

        theSpecies_->rank /= theSpecies_->size({DOMINANT, CONTESTANT});
    }

    genus->spawn();
    genus->select();
    genus->speciate();

    return;
}

void Experiment::assess(Organism* organism_, const std::vector<int> metrics_)
{
    for (const auto& metric_ : metrics_)
    {
        switch (metric_)
        {
            case NOVELTY:
                organism_->behavior = this->behavior(organism_);
                organism_->scores[NOVELTY] = this->novelty(organism_);
                break;

            case FITNESS:
                organism_->scores[FITNESS] = this->fitness(organism_);
                break;

            default:
                break;
        }

        switch (metric_)
        {
            case NOVELTY:
                if (organism_->scores[NOVELTY] >= Parameters::novelty_threshold)
                {
                    behaviors.push_back(organism_->behavior);
                    Parameters::novelty_threshold *= Parameters::novelty_threshold_modifiers[0];
                }
                else
                {
                    Parameters::novelty_threshold *= Parameters::novelty_threshold_modifiers[1];
                }
                break;

            case FITNESS:
                if (organism_->scores[FITNESS] > Parameters::fitness_threshold)
                {
                    outcome.push_back(organism_->graph());
                    Parameters::fitness_threshold = organism_->scores[FITNESS];
                }
                break;

            default:
                break;
        }
    }

    return;
}

double Experiment::novelty(Organism* organism_)
{
    if (behaviors.size() == 0)
    {
        return Parameters::novelty_threshold;
    }
    else
    {
        return Sparseness(Parameters::novelty_neighbors, behaviors, organism_->behavior);
    }
}
